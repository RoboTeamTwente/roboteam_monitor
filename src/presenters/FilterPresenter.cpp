#include "FilterPresenter.h"
#include "SeriesPresenter.h"
#include "../models/FilterModel.h"

FilterPresenter::FilterPresenter(FilterModel * model) : QObject(nullptr), model(model){}

SeriesSettingsPresenter *FilterPresenter::getParent() {
    return model->parent;
}

bool FilterPresenter::operator==(const FilterPresenter &rhs) const {
    return *model == *rhs.model;
}
bool FilterPresenter::operator!=(const FilterPresenter &rhs) const {
    return !(rhs==*this);
}
void FilterPresenter::set_value(const QString &value) {
    model->value = value;
    emit value_changed(value);
}
FilterModel *FilterPresenter::get_model() const {
    return model;
}
const QString &FilterPresenter::get_value() {
    return model->value;
}
void FilterPresenter::set_field_definition(FieldDefinition *fd) {
    model->field_definition = fd;
}
FieldDefinition *FilterPresenter::get_field_definition() {
    return model->field_definition;
}
bool FilterPresenter::is_valid() {
    return !model->value.isEmpty() && model->field_definition && model->field_definition->is_valid();
}

json FilterPresenter::to_json() {
    return {
        {"field_definition", model->field_definition->to_json()},
        {"value", model->value.toStdString()}
    };
}

