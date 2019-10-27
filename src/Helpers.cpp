#include <roboteam_utils/constants.h>
#include "Helpers.h"
#include <roboteam_proto/RobotCommand.pb.h>

//google::protobuf::Reflection * Helpers::get_reflection_for_topic(const QString &topic_name) {
//  auto topic_std = topic_name.toStdString();
//
//  if (topic_std == rtt::TOPIC_COMMANDS) {
//    return roboteam_proto::RobotCommand::GetReflection();
//  } else if (topic_std == rtt::TOPIC_WORLD_STATE) {
//  } else if (topic_std == rtt::TOPIC_FEEDBACK) {
//    proto_subscriber = new roboteam_proto::Subscriber(tcp_port_std, topic_std, &ChartSeries::handle_feedback_input, this);
//  } else if (topic_std == rtt::TOPIC_SETTINGS) {
//    proto_subscriber = new roboteam_proto::Subscriber(tcp_port_std, topic_std, &ChartSeries::handle_setting_input, this);
//  } else {
//    std::cout << "could not subscribe to topic!" << topic_std << std::endl;
//  }
//return nullptr;
//}