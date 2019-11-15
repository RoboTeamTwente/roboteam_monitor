#include "SeriesModel.h"
#include <roboteam_proto/RobotCommand.pb.h>
#include <src/models/ChartModel.h>
#include <functional>
#include <roboteam_utils/constants.h>
#include <src/views/ChartSeriesDialog.h>

using namespace google::protobuf;

SeriesModel::SeriesModel(ChartModel * chartModel, const QString & title) : QObject(nullptr), parent(chartModel) {
  qt_series = new QSplineSeries();
  settingsModel = new SeriesInputSettingsModel();

  set_name(title);
  srand (time(nullptr));
  qt_series->append(0, rand() % 20 + 1);
  qt_series->append(2, rand() % 20 + 1);
  qt_series->append(4, rand() % 20 + 1);
  qt_series->append(16, rand() % 20 + 1);
}

void SeriesModel::set_name(const QString &name) {
  qt_series->setName(name);
}

QXYSeries * SeriesModel::get_qt_series() {
  return qt_series;
}

void SeriesModel::set_visible(bool visible) {
  qt_series->setVisible(visible);
}

void SeriesModel::set_color(const QColor & color) {
  qt_series->setColor(color);
}

void SeriesModel::init_subscriber_for_channel_type(const proto::ChannelType & channel_type) {

    proto_subscriber = new proto::Subscriber<proto::RobotCommand>
        (proto::ROBOT_COMMANDS_PRIMARY_CHANNEL, &SeriesModel::handle_robot_command_input, this);

}

void SeriesModel::handle_robot_command_input(proto::RobotCommand &robot_command) {
  auto reflection = proto::RobotCommand::GetReflection();
  this->handle_incoming_message(robot_command, *reflection);
}

void SeriesModel::handle_world_input(proto::World &world) {
  auto reflection = proto::World::GetReflection();
  this->handle_incoming_message(world, *reflection);
}

void SeriesModel::handle_feedback_input(proto::RobotFeedback &feedback) {
  auto reflection = proto::RobotFeedback::GetReflection();
  this->handle_incoming_message(feedback, *reflection);
}

void SeriesModel::handle_setting_input(proto::Setting &setting) {
  auto reflection = proto::Setting::GetReflection();
  this->handle_incoming_message(setting, *reflection);
}



template<class T>
void SeriesModel::handle_incoming_message(T message, const Reflection &reflection) {
  auto current_time = roboteam_utils::Timer::getCurrentTime();
  auto field_descriptors = std::vector<const google::protobuf::FieldDescriptor *>();
  reflection.ListFields(message, &field_descriptors);


}

ChartModel *SeriesModel::get_parent() const {
    return parent;
}

void SeriesModel::set_parent(ChartModel *parent) {
    SeriesModel::parent = parent;
}

SeriesInputSettingsModel *SeriesModel::get_settings_model() const {
    return settingsModel;
}

void SeriesModel::set_settings_model(SeriesInputSettingsModel *settings_model) {
    settingsModel = settings_model;
}



