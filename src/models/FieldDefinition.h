//
// Created by Lukas Bos on 20/11/2019.
//

#ifndef RTT_FIELDDEFINITION_H
#define RTT_FIELDDEFINITION_H

#include <roboteam_utils/json.hpp>
#include <google/protobuf/descriptor.h>

using json = nlohmann::json;

class FieldDefinition {
 public:
  FieldDefinition(const google::protobuf::FieldDescriptor *field_descriptor, const std::vector<int> &field_numbers);
  FieldDefinition();
 private:
  const google::protobuf::FieldDescriptor * field_descriptor = nullptr;
 public:
  const google::protobuf::FieldDescriptor *get_field_descriptor() const;
  void set_field_descriptor(const google::protobuf::FieldDescriptor *field_descriptor);
  const std::vector<int> &get_field_numbers() const;
  json to_json();
 private:
   std::vector<int> field_numbers;
};

#endif //RTT_FIELDDEFINITION_H
