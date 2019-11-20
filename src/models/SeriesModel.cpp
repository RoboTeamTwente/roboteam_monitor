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

    google::protobuf::Reflection * refl = const_cast<Reflection *>(&reflection);


    // apply filters
    auto field_descriptors = std::vector<const google::protobuf::FieldDescriptor *>();
    reflection.ListFields(message, &field_descriptors);

    for (auto filter : settings_presenter->get_filters()) {
        // if the filter is empty do nothing
        if (!filter->get_field_definition() || !filter->get_field_definition()->get_field_descriptor() || filter->get_value().isEmpty()) break;

        if (filter->get_field_definition()->get_field_descriptor()->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_UINT32) {
            int value = reflection.GetUInt32(message, filter->get_field_definition()->get_field_descriptor());
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


        google::protobuf::Message * msg = &message;
        auto field_definition = settings_presenter->get_field_to_show();
        auto desc = message.GetDescriptor();
        google::protobuf::FieldDescriptor * field = const_cast<FieldDescriptor *>(field_definition->get_field_descriptor());
        for (int i = 0; i < field_definition->get_field_numbers().size(); i++) {
            field = const_cast<FieldDescriptor *>(desc->field(field_definition->get_field_numbers().at(i)));
            refl = const_cast<google::protobuf::Reflection *>(msg->GetReflection());



            if (field) {
                desc = field->message_type();
            }

            if (field->cpp_type() == google::protobuf::FieldDescriptor::CPPTYPE_MESSAGE) {
                msg = const_cast<Message *>(&refl->GetMessage(*msg, field));
            }
        }

        // field->extension_scope()->FindNestedTypeByName(field->na
        switch(field->cpp_type()) {
            case FieldDescriptor::CPPTYPE_INT32: {
                value = refl->GetInt32(*msg, field);
                break;
            }
            case FieldDescriptor::CPPTYPE_UINT32: {
                value = refl->GetUInt32(*msg, field);
                break;
            }
            case FieldDescriptor::CPPTYPE_INT64: {
                value = refl->GetInt64(*msg, field);
                break;
            }
            case FieldDescriptor::CPPTYPE_UINT64: {
                value = refl->GetUInt64(*msg, field);
                break;
            }
            case FieldDescriptor::CPPTYPE_FLOAT: {
                value = refl->GetFloat(*msg, field);
                break;
            }
            case FieldDescriptor::CPPTYPE_DOUBLE: {
                value = refl->GetDouble(*msg, field);
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

