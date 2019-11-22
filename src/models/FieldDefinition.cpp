#include <src/utils/Helpers.h>
#include "FieldDefinition.h"


FieldDefinition::FieldDefinition() {}

FieldDefinition::FieldDefinition(QString title, std::vector<int> field_numbers)
    : title(std::move(title)), field_numbers(std::move(field_numbers)) {}

const std::vector<int> &FieldDefinition::get_field_numbers() const {
    return field_numbers;
}

const QString &FieldDefinition::get_title() const {
    return title;
}

json FieldDefinition::to_json() {
    return {
        {"name", title.toStdString()},
        {"field_numbers", field_numbers}
    };
}

bool FieldDefinition::is_valid() {
    return !field_numbers.empty();
}

