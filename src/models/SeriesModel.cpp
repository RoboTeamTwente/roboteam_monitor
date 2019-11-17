#include "SeriesModel.h"
#include "SeriesSettingsModel.h"
#include <QtCharts/QtCharts>

SeriesModel::SeriesModel(ChartPresenter * parent) : parent(parent) {}

SeriesModel::SeriesModel(ChartPresenter * parent, QString name): parent(parent) {
    qt_series = new QSplineSeries();
    qt_series->setName(name);
    settings = new SeriesSettingsModel();

    srand (time(nullptr));
    qt_series->append(0, rand() % 20 + 1);
    qt_series->append(2, rand() % 20 + 1);
    qt_series->append(4, rand() % 20 + 1);
    qt_series->append(16, rand() % 20 + 1);
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
void SeriesModel::handle_incoming_message(T message, const google::protobuf::Reflection &reflection) {
    auto current_time = roboteam_utils::Timer::getCurrentTime();
    auto field_descriptors = std::vector<const google::protobuf::FieldDescriptor *>();
    reflection.ListFields(message, &field_descriptors);


}
ChartPresenter *SeriesModel::get_parent() const {
    return parent;
}
