//
// Created by Lukas Bos on 20/11/2019.
//

#include "FieldDefinition.h"
const google::protobuf::FieldDescriptor *FieldDefinition::get_field_descriptor() const {
    return field_descriptor;
}
void FieldDefinition::set_field_descriptor(const google::protobuf::FieldDescriptor *field_descriptor) {
    FieldDefinition::field_descriptor = field_descriptor;
}
const std::vector<int> &FieldDefinition::get_field_numbers() const {
    return field_numbers;
}
FieldDefinition::FieldDefinition(const google::protobuf::FieldDescriptor *field_descriptor,
                                 const std::vector<int> &field_numbers)
    : field_descriptor(field_descriptor), field_numbers(field_numbers) {}
FieldDefinition::FieldDefinition() {}
