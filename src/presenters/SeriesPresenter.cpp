#include "SeriesPresenter.h"
#include <src/presenters/ChartPresenter.h>
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
    model->qt_series->replace(*model->data);

    // apply the boundaries
    double margin_y = 1.05;
    auto parent = model->parent;
    parent->getxAxis()->setMin(parent->get_max_x() - 10000);
    parent->getxAxis()->setMax(parent->get_max_x() + 10);
    parent->getyAxis()->setMin(parent->get_min_y() * margin_y);
    parent->getyAxis()->setMax(parent->get_max_y() * margin_y);

}
