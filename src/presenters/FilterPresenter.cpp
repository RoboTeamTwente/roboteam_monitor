#include "FilterPresenter.h"
#include "SeriesPresenter.h"
#include "../models/FilterModel.h"

FilterPresenter::FilterPresenter(FilterModel * model) : model(model){}

SeriesSettingsPresenter *FilterPresenter::getParent() {
    return model->parent;
}

