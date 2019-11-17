#include "FilterPresenter.h"
#include "SeriesPresenter.h"
#include "../models/FilterModel.h"

FilterPresenter::FilterPresenter(FilterModel * model) : model(model){}

SeriesInputSettingsPresenter *FilterPresenter::getParent() {
    return model->parent;
}

