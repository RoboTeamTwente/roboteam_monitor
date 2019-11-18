#include "SeriesModel.h"
#include "SeriesSettingsModel.h"
#include <QtCharts/QtCharts>

SeriesModel::SeriesModel(ChartPresenter * parent, const QString & name): parent(parent) {
    time_since_series_is_created = timer.getCurrentTime().count();
    qt_series = new QSplineSeries();
    qt_series->setName(name);
    settings = new SeriesSettingsModel(new SeriesPresenter(this));
    init_subscriber_for_channel_type(proto::ChannelType::GEOMETRY_CHANNEL);
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

    auto now = timer.getCurrentTime();

    if (now.count() <= lastRateUpdateTime + 1000) {
        rate++;
    } else {
        lastRateUpdateTime = now.count();
        QPoint point((now.count() - time_since_series_is_created)/1000, rate);
        data.append(point);
        std::cout << "adding data: " << point.x() << ", " << point.y() << std::endl;
        qt_series->replace(data);
        parent->adjustBoundaries(point.x(), point.y());
        parent->getxAxis()->applyNiceNumbers();
        rate = 0;
    }
}

ChartPresenter *SeriesModel::get_parent() const {
    return parent;
}

