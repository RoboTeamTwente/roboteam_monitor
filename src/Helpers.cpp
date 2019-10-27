#include <roboteam_utils/constants.h>
#include "Helpers.h"
#include <roboteam_proto/RobotCommand.pb.h>
#include <roboteam_proto/RobotFeedback.pb.h>
#include <roboteam_proto/Setting.pb.h>
#include <roboteam_proto/World.pb.h>
#include <roboteam_proto/messages_robocup_ssl_geometry.pb.h>
#include <roboteam_proto/messages_robocup_ssl_referee.pb.h>

const google::protobuf::Descriptor * Helpers::get_descriptor_for_topic(const QString &topic_name) {
    auto channel_type = getChannelTypeByName(topic_name);
    switch(channel_type) {
        case roboteam_utils::ROBOT_COMMANDS_PRIMARY_CHANNEL: // fall through
        case roboteam_utils::ROBOT_COMMANDS_SECONDARY_CHANNEL: {
            return proto::RobotCommand::GetDescriptor();
        }
        case roboteam_utils::FEEDBACK_PRIMARY_CHANNEL: // fall through
        case roboteam_utils::FEEDBACK_SECONDARY_CHANNEL: {
            return proto::RobotFeedback::GetDescriptor();
        }
        case roboteam_utils::SETTINGS_PRIMARY_CHANNEL: // fall through
        case roboteam_utils::SETTINGS_SECONDARY_CHANNEL: {
            return proto::Setting::GetDescriptor();
        }
        case roboteam_utils::GEOMETRY_CHANNEL: {
            return proto::SSL_GeometryData::GetDescriptor();
        }
        case roboteam_utils::WORLD_CHANNEL: {
            return proto::World::GetDescriptor();
        }
        case roboteam_utils::REFEREE_CHANNEL: {
            return proto::SSL_Referee::GetDescriptor();
        }
        default: return nullptr;
    }
}

roboteam_utils::ChannelType Helpers::getChannelTypeByName(const QString &topic_name) {
    auto topic_std = topic_name.toStdString();

    for (auto const & channel_pair : roboteam_utils::CHANNELS) {
        if (channel_pair.second.name == topic_std) {
            return channel_pair.first;
        }
    }
    return roboteam_utils::UNDEFINED_CHANNEL;
}
