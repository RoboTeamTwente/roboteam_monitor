#include <src/utils/Helpers.h>
#include "FieldDefinition.h"

// Constructor
FieldDefinition::FieldDefinition(QString title, std::vector<int> field_numbers)
    : title(std::move(title)), field_numbers(std::move(field_numbers)) {}

// Generate a model from a JSON object
FieldDefinition::FieldDefinition(const json & data) {
    field_numbers = data.value("field_numbers", field_numbers);
    title = QString::fromStdString(data.value("name", title.toStdString()));
}

// check if the field definition is valid (e.g. it has a set of field numbers set)
bool FieldDefinition::is_valid() {
    return !field_numbers.empty();
}

// Generate a JSON object from the model
json FieldDefinition::to_json() {
    return {
        {"name", title.toStdString()},
        {"field_numbers", field_numbers}
    };
}

const std::vector<int> &FieldDefinition::get_field_numbers() const {
    return field_numbers;
}

const QString &FieldDefinition::get_title() const {
    return title;
}

bool FieldDefinition::operator==(const FieldDefinition &rhs) const {
    return title==rhs.title &&
        field_numbers==rhs.field_numbers;
}

bool FieldDefinition::operator!=(const FieldDefinition &rhs) const {
    return !(rhs==*this);
}

FieldDefinition * FieldDefinition::get_copy() {
    return new FieldDefinition(title, field_numbers);;
}
