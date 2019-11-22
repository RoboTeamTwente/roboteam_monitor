#include "SeriesPresenter.h"
#include "SeriesSettingsPresenter.h"
#include "ChartPresenter.h"
#include <src/views/SeriesSettingsDialog.h>
#include "models/SeriesModel.h"

using namespace google::protobuf;

SeriesPresenter::SeriesPresenter(SeriesModel * model) : QObject(nullptr), model(model) {}

void SeriesPresenter::set_name(const QString &name) {
  model->qt_series->setName(name);
}

QXYSeries * SeriesPresenter::get_qt_series() {
  return model->qt_series;
}

void SeriesPresenter::set_visible(bool visible) {
    model->qt_series->setVisible(visible);
}

void SeriesPresenter::set_color(const QColor & color) {
    model->qt_series->setColor(color);
}
SeriesSettingsPresenter * SeriesPresenter::getSettings() {
    return model->settings_presenter;
}

ChartPresenter *SeriesPresenter::getParent() {
    return model->parent;
}

void SeriesPresenter::start_new_subscription() {
    model->qt_series->clear();
    model->init_subscriber_for_channel_type(getSettings()->get_channel_type());
}

int SeriesPresenter::get_rate() {
    return model->rate;
}
SeriesSettingsPresenter *SeriesPresenter::get_settings_copy() {
    return new SeriesSettingsPresenter(getSettings()->get_model_copy());
}
void SeriesPresenter::applySettings(SeriesSettingsPresenter *new_settings) {
    model->settings_presenter = new_settings;
}

void SeriesPresenter::apply_data() {
    // apply the data
    model->qt_series->clear();
    model->qt_series->replace(*model->data);
}

SeriesPresenter::~SeriesPresenter() {
delete model;
}

void SeriesPresenter::clear_data() {
    model->data->clear();
}

json SeriesPresenter::to_json() {
    return model->to_json();
}
int SeriesPresenter::get_filtered_packets_rate() {
    return model->filtered_packets;
}
