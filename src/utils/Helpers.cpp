#include "Helpers.h"
#include <roboteam_proto/RobotCommand.pb.h>
#include <roboteam_proto/RobotFeedback.pb.h>
#include <roboteam_proto/Setting.pb.h>
#include <roboteam_proto/World.pb.h>
#include <roboteam_proto/messages_robocup_ssl_geometry.pb.h>
#include <roboteam_proto/messages_robocup_ssl_referee.pb.h>
#include <roboteam_proto/Channels.h>
#include <QWidget>
#include <optional>

const google::protobuf::Descriptor * Helpers::get_descriptor_for_topic(const QString &topic_name) {
    auto channel_type = getChannelTypeByName(topic_name);
    switch(channel_type) {
        case proto::ROBOT_COMMANDS_PRIMARY_CHANNEL: // fall through
        case proto::ROBOT_COMMANDS_SECONDARY_CHANNEL: {
            return proto::RobotCommand::GetDescriptor();
        }
        case proto::FEEDBACK_PRIMARY_CHANNEL: // fall through
        case proto::FEEDBACK_SECONDARY_CHANNEL: {
            return proto::RobotFeedback::GetDescriptor();
        }
        case proto::SETTINGS_PRIMARY_CHANNEL: // fall through
        case proto::SETTINGS_SECONDARY_CHANNEL: {
            return proto::Setting::GetDescriptor();
        }
        case proto::GEOMETRY_CHANNEL: {
            return proto::SSL_GeometryData::GetDescriptor();
        }
        case proto::WORLD_CHANNEL: {
            return proto::World::GetDescriptor();
        }
        case proto::REFEREE_CHANNEL: {
            return proto::SSL_Referee::GetDescriptor();
        }
        default: return nullptr;
    }
}

proto::ChannelType Helpers::getChannelTypeByName(const QString &topic_name) {
    auto topic_std = topic_name.toStdString();

    for (auto const & channel_pair : proto::CHANNELS) {
        if (channel_pair.second.name == topic_std) {
            return channel_pair.first;
        }
    }
    return proto::UNDEFINED_CHANNEL;
}

QString Helpers::get_actual_typename(const google::protobuf::FieldDescriptor * field_descriptor) {
    auto cpp_type_name = field_descriptor->cpp_type_name();
    if (QString::fromStdString(cpp_type_name) == "message") {
        return QString::fromStdString(field_descriptor->message_type()->name());
    }
    return cpp_type_name;
}

void Helpers::clearLayout(QLayout* layout) {
    QLayoutItem* item;
    while ((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
            delete item->widget();
        }
    }
}

int Helpers::frequency_hz_to_millis(int frequency) {
    return (1.0/static_cast<int>(frequency))*1000;
}

/*
 * Convert a message and field definition to a submessage and field descriptor.
 * With this format we can easily retrieve a value from a message.
 */
std::pair<Message*, FieldDescriptor*> Helpers::getDescriptorFromDefinition(Message * msg, FieldDefinition * field_definition) {
    if (!field_definition || !msg) return {};

    // these variables get updated in the loop
    Reflection * reflection = nullptr;
    FieldDescriptor * field = nullptr;
    auto desc = msg->GetDescriptor();

    // iterate over the field numbers in the definition to extract the field descriptor and submessage from the message
    for (int index : field_definition->get_field_numbers()) {
        field = const_cast<FieldDescriptor *>(desc->field(index));
        reflection = const_cast<Reflection *>(msg->GetReflection());

        // if the field has a message type then it must be the submessage
        if (field && field->cpp_type()==FieldDescriptor::CPPTYPE_MESSAGE) {
            desc = field->message_type();
            msg = const_cast<Message *>(&reflection->GetMessage(*msg, field));
        }
    }
    return {msg, field};
}

std::optional<double> Helpers::get_numeric_value(Message *message, FieldDefinition *field_definition) {
    if (!message || !field_definition) return std::nullopt;
    auto [msg, field] = getDescriptorFromDefinition(message, field_definition);
    auto refl = const_cast<Reflection *>(msg->GetReflection());

    switch(field->cpp_type()) {
        case FieldDescriptor::CPPTYPE_INT32: return refl->GetInt32(*msg, field);
        case FieldDescriptor::CPPTYPE_UINT32: return refl->GetUInt32(*msg, field);
        case FieldDescriptor::CPPTYPE_INT64: return refl->GetInt64(*msg, field);
        case FieldDescriptor::CPPTYPE_UINT64: return refl->GetUInt64(*msg, field);
        case FieldDescriptor::CPPTYPE_FLOAT: return refl->GetFloat(*msg, field);
        case FieldDescriptor::CPPTYPE_DOUBLE: return refl->GetDouble(*msg, field);
    }
    return std::nullopt;
}
