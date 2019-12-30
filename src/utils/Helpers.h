#ifndef RTT_HELPERS_H
#define RTT_HELPERS_H

#include <QString>
#include <roboteam_proto/Channels.h>
#include <google/protobuf/descriptor.h>
#include <QLayout>
#include <src/models/FieldDefinition.h>
#include <optional>

using namespace google::protobuf;

class Helpers {
 public:
  static const Descriptor * get_descriptor_for_topic(const QString & topic_name);
  static proto::ChannelType getChannelTypeByName(const QString & topic_name);

  /*
   * The default field_descriptor.cpp_type() returned only basic types or 'message'.
   * This function also translates the 'message' types to their real ones, for example float2f
   */
  static QString get_actual_typename(const FieldDescriptor * field_descriptor);
  static void clearLayout(QLayout* layout);
  static int frequency_hz_to_millis(int frequency);
  static std::pair<const Message*, const FieldDescriptor*> getDescriptorFromDefinition(const Message * msg, FieldDefinition * field_definition);
  static std::optional<double> get_numeric_value(const Message * msg, FieldDefinition * field_definition);
  };


#endif //RTT_HELPERS_H
