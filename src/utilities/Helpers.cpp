#include "Helpers.h"
#include <roboteam_proto/RobotCommand.pb.h>
#include <roboteam_proto/RobotFeedback.pb.h>
#include <roboteam_proto/Setting.pb.h>
#include <roboteam_proto/World.pb.h>
#include <roboteam_proto/messages_robocup_ssl_geometry.pb.h>
#include <roboteam_proto/messages_robocup_ssl_referee.pb.h>
#include <roboteam_proto/Channels.h>
#include <QLayout>
#include <QLayoutItem>
#include <QWidget>

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
    if (field_descriptor) {
        auto cpp_type_name = field_descriptor->cpp_type_name();
        if (QString::fromStdString(cpp_type_name)=="message") {
            return QString::fromStdString(field_descriptor->message_type()->name());
        }
        return cpp_type_name;
    }
    return "Empty Filter";
}

void Helpers::clearLayout(QLayout *layout) {
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
            delete item->widget();
        }
    }
}
