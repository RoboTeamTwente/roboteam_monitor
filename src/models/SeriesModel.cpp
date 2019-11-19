#include "SeriesModel.h"
#include "SeriesSettingsModel.h"
#include <QtCharts/QtCharts>

using namespace google::protobuf;

SeriesModel::SeriesModel(ChartPresenter * parent, const QString & name): parent(parent) {
    time_since_series_is_created = timer.getCurrentTime().count();
    qt_series = new QLineSeries();
    qt_series->setName(name);
    auto settings = new SeriesSettingsModel(new SeriesPresenter(this));
    settings_presenter = new SeriesSettingsPresenter(settings);
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


    // apply filters

    auto field_descriptors = std::vector<const google::protobuf::FieldDescriptor *>();
    reflection.ListFields(message, &field_descriptors);

    for (auto filter : settings_presenter->get_filters()) {
        // if the filter is empty do nothing
        if (!filter->get_field_descriptor() || filter->get_value().isEmpty()) break;

        if (filter->get_field_descriptor()->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_UINT32) {
            int value = reflection.GetUInt32(message, filter->get_field_descriptor());
            if (QString::number(value, 10) != filter->get_value()) return;
        } else {
            return;
        }
    }

    // handle rate
    auto now = timer.getCurrentTime();
    if (now.count() <= lastRateUpdateTime + 1000) {
        rate++;
    } else {
        lastRateUpdateTime = now.count();
        QPoint point((now.count() - parent->get_time_chart_created())/1000.0, rate);

        if (settings_presenter->use_packet_rate()) {
            qt_series->append(point);
        }
        parent->adjustBoundaries(point.x(), point.y());
        rate = 0;
    }


    auto time = (now.count() - parent->get_time_chart_created())/1000.0;
    double value = 0;

    // handle custom fields
    if (!settings_presenter->use_packet_rate()) {
    if (settings_presenter->get_field_to_show()) {

        switch(settings_presenter->get_field_to_show()->cpp_type()) {
            case FieldDescriptor::CPPTYPE_INT32: {
                value = reflection.GetInt32(message, settings_presenter->get_field_to_show());
                break;
            }
            case FieldDescriptor::CPPTYPE_UINT32: {
                value = reflection.GetUInt32(message, settings_presenter->get_field_to_show());
                break;
            }
            case FieldDescriptor::CPPTYPE_INT64: {
                value = reflection.GetInt64(message, settings_presenter->get_field_to_show());
                break;
            }
            case FieldDescriptor::CPPTYPE_UINT64: {
                value = reflection.GetUInt64(message, settings_presenter->get_field_to_show());
                break;
            }
            case FieldDescriptor::CPPTYPE_FLOAT: {
                value = reflection.GetFloat(message, settings_presenter->get_field_to_show());
                break;
            }
            case FieldDescriptor::CPPTYPE_DOUBLE: {
                value = reflection.GetDouble(message, settings_presenter->get_field_to_show());
                break;
            }
            default: return;

        }
        QPoint point(time, value);
        qt_series->append(point);
        parent->adjustBoundaries(point.x(), point.y());


     }

    }
}

ChartPresenter *SeriesModel::get_parent() const {
    return parent;
}

