//
// Created by Lukas Bos on 21/10/2019.
//

#ifndef RTT_HELPERS_H
#define RTT_HELPERS_H

#include <google/protobuf/message.h>
#include <QString>

class Helpers {
 public:
  static const google::protobuf::Descriptor * get_descriptor_for_topic(const QString & topic_name);
  static roboteam_utils::ChannelType getChannelTypeByName(const QString & topic_name);
};


#endif //RTT_HELPERS_H
