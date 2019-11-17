#include "SeriesPresenter.h"
#include <roboteam_proto/RobotCommand.pb.h>
#include <src/presenters/ChartPresenter.h>
#include <functional>
#include <roboteam_utils/constants.h>
#include <src/views/ChartSeriesDialog.h>
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
    return new SeriesSettingsPresenter(model->settings);
}
ChartPresenter *SeriesPresenter::getParent() {
    return model->parent;
}

