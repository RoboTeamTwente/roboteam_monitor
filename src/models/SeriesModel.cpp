#include "SeriesModel.h"
#include "SeriesSettingsModel.h"
#include <QtCharts/QtCharts>
#include <src/utils/Helpers.h>
#include <src/utils/Constants.h>

using namespace google::protobuf;

SeriesModel::SeriesModel(ChartPresenter * parent, const QString & name): parent(parent) {
    time_since_series_is_created = timer.getCurrentTime().count();
    qt_series = new QLineSeries();
    qt_series->setName(name);
    data = new QList<QPointF>();
    auto settings = new SeriesSettingsModel(new SeriesPresenter(this));
    settings_presenter = new SeriesSettingsPresenter(settings);
    init_subscriber_for_channel_type(proto::ChannelType::GEOMETRY_CHANNEL);
}


void SeriesModel::init_subscriber_for_channel_type(const proto::ChannelType & channel_type) {
    if (!proto_subscriber) {

        proto_subscriber = reinterpret_cast<proto::Subscriber<Message> *>(
            new proto::Subscriber<proto::RobotCommand>(proto::ROBOT_COMMANDS_PRIMARY_CHANNEL,
                                                       &SeriesModel::handle_incoming_message,
                                                       this));
    }



    std::cerr << "[SeriesModel:init_subscriber_for_channel_type] temporarily only allowing one type of publisher" << std::endl;
}


/*
 *
 * This function currently applies every setting available to the incoming messages.
 * - applying filters
 * - measuring rate
 * - forwarding output
 *
 */
template<class T>
void SeriesModel::handle_incoming_message(T message) {
    for (auto filter : settings_presenter->get_filters()) {
        // if the filter is empty do nothing
        if (!filter->get_field_definition() || filter->get_value().isEmpty()) break;

        // if the filter is not satisfied then return
        std::optional<double> value = Helpers::get_numeric_value(&message, filter->get_field_definition());

        if (!value.has_value() || QString::number(static_cast<int>(value.value()), 10) != filter->get_value()) {
            internal_filtered_packets++;
            return;
        };
    }

    // handle rate
    auto current_time = roboteam_utils::Timer::getCurrentTime();
    auto now = timer.getCurrentTime();
    determine_packet_rate();

    if (settings_presenter->use_packet_rate()) {
        QPoint point((now.count() - parent->get_time_chart_created())/1000.0, rate);
        data->push_back(point);
        parent->adjustBoundaries(point.x(), point.y(), 10);
    } else {
        if (settings_presenter->get_field_to_show()) {
            auto value = Helpers::get_numeric_value(&message, settings_presenter->get_field_to_show());
            if (value) {
                qreal time = (now.count() - parent->get_time_chart_created());
                QPoint point(time, value.value());
                parent->adjustBoundaries(point.x(), point.y(), 10);
                data->push_back(point);
            }
        }
    }
    while(data->size() > MAX_BUFFER_SIZE) {
        data->pop_front();
    }
}
void SeriesModel::determine_packet_rate() {
    if (roboteam_utils::Timer::getCurrentTime().count() <= lastRateUpdateTime + 1000) {
        internal_rate++;
    } else {
        lastRateUpdateTime = roboteam_utils::Timer::getCurrentTime().count();
        rate = internal_rate;
        filtered_packets = internal_filtered_packets;
        internal_rate = 0;
        internal_filtered_packets = 0;
    }
}

ChartPresenter *SeriesModel::get_parent() const {
    return parent;
}
SeriesModel::~SeriesModel() {
    /*
     * Ignore the clang-tidy warning here.
     * clang-tidy thinks proto_subscriber == nullptr, but it is not.
     */

    // NOLINTNEXTLINE
    if (proto_subscriber) {
        delete proto_subscriber;
    }
}

json SeriesModel::to_json() {
    return {
        {"settings", settings_presenter->get_model_copy()->to_json()}
    };
}




