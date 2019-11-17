//
// Created by Lukas Bos on 17/11/2019.
//

#include <google/protobuf/descriptor.h>
#include "FilterModel.h"

google::protobuf::FieldDescriptor *FilterModel::get_field_descriptor() const {
    return field_descriptor;
}
void FilterModel::set_field_descriptor(google::protobuf::FieldDescriptor *field_descriptor) {
    FilterModel::field_descriptor = field_descriptor;
}
google::protobuf::Message *FilterModel::get_reference_message() const {
    return reference_message;
}
void FilterModel::set_reference_message(google::protobuf::Message *reference_message) {
    FilterModel::reference_message = reference_message;
}
const QString &FilterModel::get_value() const {
    return value;
}
void FilterModel::set_value(const QString &value) {
    FilterModel::value = value;
}