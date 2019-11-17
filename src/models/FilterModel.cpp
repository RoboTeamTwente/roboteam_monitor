//
// Created by Lukas Bos on 17/11/2019.
//

#include <google/protobuf/descriptor.h>
#include "FilterModel.h"

FilterModel::FilterModel(SeriesSettingsPresenter * parent) : parent(parent) {}


FilterModel::FilterModel(SeriesSettingsPresenter * parent, google::protobuf::FieldDescriptor *field_descriptor,
                         google::protobuf::Message *reference_message,
                         QString value)
    : field_descriptor(field_descriptor), reference_message(reference_message), value(std::move(value)), parent(parent)
    {}


bool FilterModel::operator==(const FilterModel &other) {
    return field_descriptor == other.field_descriptor && reference_message == other.reference_message && value == other.value;
}


