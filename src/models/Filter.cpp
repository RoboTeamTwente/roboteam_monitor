//
// Created by Lukas Bos on 12/11/2019.
//

#include "filter.h"

Filter::Filter(google::protobuf::FieldDescriptor * field_descriptor, QString value)
: field_descriptor(field_descriptor), value(value) {

}
google::protobuf::FieldDescriptor *Filter::get_field_descriptor() const {
    return field_descriptor;
}
void Filter::set_field_descriptor(google::protobuf::FieldDescriptor *field_descriptor) {
    Filter::field_descriptor = field_descriptor;
}
const QString &Filter::get_value() const {
    return value;
}
void Filter::set_value(const QString &value) {
    Filter::value = value;
}

Filter::Filter(const Filter &other) {
    set_field_descriptor(other.get_field_descriptor());
    set_value(other.get_value());
}

Filter::~Filter() {
delete field_descriptor;
}
