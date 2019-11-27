#include "SeriesModel.h"
#include "SeriesSettingsModel.h"
#include <QtCharts/QtCharts>
#include <src/utils/Helpers.h>
#include <src/utils/Constants.h>
#include <src/presenters/SeriesSettingsPresenter.h>

using namespace google::protobuf;

SeriesModel::SeriesModel(ChartPresenter * parent, const QString & name): parent(parent) {
    time_since_series_is_created = timer.getCurrentTime().count();
    qt_series = new QLineSeries();
    qt_series->setName(name);
    data = new QList<QPointF>();
    auto settings = new SeriesSettingsModel(new SeriesPresenter(this));
    settings_presenter = new SeriesSettingsPresenter(settings);
    init_subscriber(proto::ChannelType::GEOMETRY_CHANNEL);
}


void SeriesModel::init_subscriber(const proto::ChannelType & channel_type, const QString & ip_config) {

    if (!proto_subscriber) {
        auto sub = new proto::Subscriber<proto::RobotCommand>(proto::ROBOT_COMMANDS_PRIMARY_CHANNEL,
                                                              &SeriesModel::handle_incoming_message,
                                                              this, ip_config.toStdString());

        proto_subscriber = reinterpret_cast<proto::Subscriber<Message> *>(sub);
    }



    std::cerr << "[SeriesModel:init_subscriber] temporarily only allowing one type of publisher" << std::endl;
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
    auto now = std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::steady_clock::now().time_since_epoch()
    );

    determine_packet_rate();
    qreal time = (now.count() - parent->get_time_chart_created())/1000000.0;


    if (settings_presenter->use_packet_rate()) {
        QPointF point(time, rate);
        data->push_back(point);
        parent->adjustBoundaries(point.x(), point.y(), 10);
    } else {
        if (settings_presenter->get_field_to_show()) {
            auto value = Helpers::get_numeric_value(&message, settings_presenter->get_field_to_show());
            if (value) {
                QPointF point(time, value.value());
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
    destroy_subscriber();
}

json SeriesModel::to_json() {
    return {
        {"name", qt_series->name().toStdString()},
        {"settings", settings_presenter->get_model_copy()->to_json()}
    };
}

SeriesModel::SeriesModel(ChartPresenter *parent, json json_data) : parent(parent) {

    auto json_name = json_data.value("name", "Series");
    json json_settings = json_data["settings"];

    time_since_series_is_created = timer.getCurrentTime().count();
    qt_series = new QLineSeries();
    qt_series->setName(QString::fromStdString(json_name));
    data = new QList<QPointF>();


    auto series_presenter = new SeriesPresenter(this);
    auto settings = new SeriesSettingsModel(series_presenter);

    if (!json_settings.is_null()) {
        settings = new SeriesSettingsModel(series_presenter, json_settings);
    }

    settings_presenter = new SeriesSettingsPresenter(settings);
    init_subscriber(proto::ChannelType::GEOMETRY_CHANNEL);
}

void SeriesModel::destroy_subscriber() {
    /*
     * Ignore the clang-tidy warning here.
     * clang-tidy thinks proto_subscriber == nullptr, but it is not.
     */

    // NOLINTNEXTLINE
    if (proto_subscriber) {
        delete proto_subscriber;
    }
}

void SeriesModel::reboot_subscriber() {
    destroy_subscriber();
    std::cout << "rebooting with ip: " << parent->get_ip_config().toStdString() << std::endl;
    init_subscriber(settings_presenter->get_channel_type(), parent->get_ip_config());
}




