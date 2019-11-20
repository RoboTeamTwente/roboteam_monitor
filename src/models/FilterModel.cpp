//
// Created by Lukas Bos on 17/11/2019.
//

#include <google/protobuf/descriptor.h>
#include <src/utils/Helpers.h>
#include "FilterModel.h"

FilterModel::FilterModel(SeriesSettingsPresenter * parent) : parent(parent) {}


FilterModel::FilterModel(SeriesSettingsPresenter * parent, FieldDefinition * field_definition,
                         google::protobuf::Message *reference_message,
                         QString value)
    : field_definition(field_definition), reference_message(reference_message), value(std::move(value)), parent(parent)
    {}


bool FilterModel::operator==(const FilterModel &other) {
    return false;
//    return  ((
//        (field_definition && other.field_definition) &&
//        (Helpers::get_actual_typename(field_descriptor) == Helpers::get_actual_typename(other.field_descriptor)) &&
//        (field_definition == other.field_descriptor))
//    || (!field_descriptor && !other.field_descriptor))
//    && reference_message == other.reference_message
//    && value == other.value;
}


