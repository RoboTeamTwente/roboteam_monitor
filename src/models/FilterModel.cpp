//
// Created by Lukas Bos on 17/11/2019.
//

#include <google/protobuf/descriptor.h>
#include <src/utils/Helpers.h>
#include "FilterModel.h"

// default constructor
FilterModel::FilterModel(SeriesSettingsPresenter * parent) : parent(parent) {}

// constructor
FilterModel::FilterModel(SeriesSettingsPresenter * parent, FieldDefinition * field_definition, QString value)
    : field_definition(field_definition), value(std::move(value)), parent(parent)
    {}

// constructor from JSON object
FilterModel::FilterModel(SeriesSettingsPresenter *parent, json data) : parent(parent){
    json field_definition_json = data["field_definition"];
    if (!field_definition_json.is_null()) {
        field_definition = new FieldDefinition(field_definition_json);
    }
    value = QString::fromStdString(data.value("value", value.toStdString()));
}


bool FilterModel::operator==(const FilterModel &other) {
    return field_definition == other.field_definition && value == other.value;
}

// Generate a JSON object that represents this model.
json FilterModel::to_json() {
    return {
        {"field_definition", field_definition->to_json()},
        {"value", value.toStdString()}
    };
}


