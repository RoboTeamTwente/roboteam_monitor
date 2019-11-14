#include "include/models/SeriesModel.h"
#include <roboteam_proto/RobotCommand.pb.h>
#include <include/models/ChartModel.h>
#include <functional>
#include <roboteam_utils/constants.h>
#include <ChartSeriesDialog.h>

using namespace google::protobuf;

SeriesModel::SeriesModel(ChartModel * chartModel) : QObject(nullptr), parent(chartModel) {
  qt_series = new QSplineSeries();
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

void SeriesModel::update_channel(const proto::ChannelType & channel_type) {
  if (this->channel_type != channel_type) {
    this->channel_type = channel_type;
    init_subscriber_for_channel_type(channel_type);
  }
}

template<class T>
void SeriesModel::handle_incoming_message(T message, const Reflection &reflection) {
  auto current_time = roboteam_utils::Timer::getCurrentTime();
  auto field_descriptors = std::vector<const google::protobuf::FieldDescriptor *>();
  reflection.ListFields(message, &field_descriptors);

  for (auto field_descriptor : field_descriptors) {
    switch(field_descriptor->cpp_type()) {
      case FieldDescriptor::CPPTYPE_FLOAT: break;
      case FieldDescriptor::CPPTYPE_INT32: break;
      default: break;
    }
  }
}

const std::vector<Filter *> &SeriesModel::get_filters() {
    return filters;
}

Filter * SeriesModel::add_new_filter() {
    auto empty_filter = new Filter();
    filters.push_back(empty_filter);
    return empty_filter;
}

void SeriesModel::removeFilter(Filter *filter_to_remove) {
    filters.erase(std::remove(filters.begin(), filters.end(), filter_to_remove), filters.end());
}
ChartModel *SeriesModel::get_parent() const {
    return parent;
}
void SeriesModel::set_parent(ChartModel *parent) {
    SeriesModel::parent = parent;
}



