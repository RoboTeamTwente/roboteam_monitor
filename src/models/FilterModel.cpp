//
// Created by Lukas Bos on 17/11/2019.
//

#include <google/protobuf/descriptor.h>
#include <src/utils/Helpers.h>
#include "FilterModel.h"


FilterModel::FilterModel(SeriesSettingsPresenter * parent) : parent(parent) {}


FilterModel::FilterModel(SeriesSettingsPresenter * parent, FieldDefinition * field_definition,
                         QString value)
    : field_definition(field_definition), value(std::move(value)), parent(parent)
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

json FilterModel::to_json() {
    return {
        {"field_definition", field_definition->to_json()},
        {"value", value.toStdString()}
    };
}
FilterModel::FilterModel(SeriesSettingsPresenter *parent, json data) : parent(parent){
    json field_definition_json = data["field_definition"];
    if (!field_definition_json.is_null()) {
        field_definition = new FieldDefinition(field_definition_json);
    }
    value = QString::fromStdString(data.value("value", value.toStdString()));
}

