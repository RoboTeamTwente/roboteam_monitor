#include "FilterModel.h"
FilterModel::FilterModel(google::protobuf::FieldDescriptor *field_descriptor,
                         google::protobuf::Message *reference_message,
                         const QString &value)
    : field_descriptor(field_descriptor), reference_message(reference_message), value(value) {}

FilterModel::FilterModel() {}

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
FilterModel *FilterModel::clone() {
    auto clone = new FilterModel();
    clone->set_field_descriptor(field_descriptor);
    clone->set_value(value);
    clone->set_reference_message(reference_message);
    return clone;
}

bool FilterModel::operator==(const FilterModel &other) {
    return field_descriptor == other.get_field_descriptor() && reference_message == other.get_reference_message() && value == other.get_value();
}
