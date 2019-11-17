//
// Created by Lukas Bos on 21/10/2019.
//

#ifndef RTT_HELPERS_H
#define RTT_HELPERS_H

#include <QString>
#include <roboteam_proto/Channels.h>
#include <google/protobuf/descriptor.h>
#include <QLayout>

class Helpers {
 public:
  static const google::protobuf::Descriptor * get_descriptor_for_topic(const QString & topic_name);
  static proto::ChannelType getChannelTypeByName(const QString & topic_name);

  /*
   * The default field_descriptor.cpp_type() returned only basic types or 'message'.
   * This function also translates the 'message' types to their real ones, for example float2f
   */
  static QString get_actual_typename(const google::protobuf::FieldDescriptor * field_descriptor);
  static void clearLayout(QLayout* layout);

};


#endif //RTT_HELPERS_H
