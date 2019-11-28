#include "SeriesPresenter.h"
#include "SeriesSettingsPresenter.h"
#include "ChartPresenter.h"
#include <src/views/SeriesSettingsDialog.h>
#include "models/SeriesModel.h"
#include <src/utils/Constants.h>
#include <QtCharts/QtCharts>
#include <src/utils/Helpers.h>

using namespace google::protobuf;

SeriesPresenter::SeriesPresenter(SeriesModel * model) : QObject(nullptr), model(model) {
    time_since_series_is_created = timer.getCurrentTime().count();
    qt_series = new QLineSeries();
    qt_series->setName("series name");
    data = new QList<QPointF>();

    getParent()->get_subscription_manager()->register_series(this);

}

void SeriesPresenter::set_name(const QString &name) {
  qt_series->setName(name);
}

QXYSeries * SeriesPresenter::get_qt_series() {
  return qt_series;
}

void SeriesPresenter::set_visible(bool visible) {
    qt_series->setVisible(visible);
}

void SeriesPresenter::set_color(const QColor & color) {
    qt_series->setColor(color);
}
SeriesSettingsPresenter * SeriesPresenter::getSettings() {
    return model->settings_presenter;
}

ChartPresenter *SeriesPresenter::getParent() {
    return model->parent;
}

void SeriesPresenter::start_new_subscription() {
    qt_series->clear();
//    init_subscriber(getSettings()->get_channel_type());
}

int SeriesPresenter::get_rate() {
    return rate;
}
SeriesSettingsPresenter *SeriesPresenter::get_settings_copy() {
    return new SeriesSettingsPresenter(getSettings()->get_model_copy());
}
void SeriesPresenter::applySettings(SeriesSettingsPresenter *new_settings) {
    model->settings_presenter = new_settings;
}

void SeriesPresenter::apply_data() {
    // apply the data
    qt_series->clear();
    qt_series->replace(*data);
}

SeriesPresenter::~SeriesPresenter() {
    getParent()->get_subscription_manager()->remove_series(this);
    delete model;
}

void SeriesPresenter::clear_data() {
    data->clear();
}

json SeriesPresenter::to_json() {
    return model->to_json();
}
int SeriesPresenter::get_filtered_packets_rate() {
    return filtered_packets;
}
void SeriesPresenter::reboot_subscriber() {
  //  model->reboot_subscriber();
}


void SeriesPresenter::determine_packet_rate() {
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

void SeriesPresenter::handle_incoming_message(google::protobuf::Message * message) {
    if (message_is_filtered(message)) return;

    // handle rate
    auto now = std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::steady_clock::now().time_since_epoch()
    );

    determine_packet_rate();
    qreal time = (now.count() - model->get_parent()->get_time_chart_created())/1000000.0;


    if (getSettings()->use_packet_rate()) {
        QPointF point(time, rate);
        data->push_back(point);
        model->get_parent()->adjustBoundaries(point.x(), point.y(), 10);
    } else {
        if (getSettings()->get_field_to_show()) {
            auto value = Helpers::get_numeric_value(message, getSettings()->get_field_to_show());
            if (value) {
                QPointF point(time, value.value());
                model->get_parent()->adjustBoundaries(point.x(), point.y(), 10);
                data->push_back(point);
            }
        }
    }
    while(data->size() > MAX_BUFFER_SIZE) {
        data->pop_front();
    }
}
bool SeriesPresenter::message_is_filtered(google::protobuf::Message * message) {
    for (auto filter : getSettings()->get_filters()) {
        // if the filter is empty do nothing
        if (!filter->get_field_definition() || filter->get_value().isEmpty()) break;

        // if the filter is not satisfied then return
        std::optional<double> value = Helpers::get_numeric_value(message, filter->get_field_definition());

        if (!value.has_value() || QString::number(static_cast<int>(value.value()), 10) != filter->get_value()) {
            internal_filtered_packets++;
            return true;
        }
    }
    return false;
}
