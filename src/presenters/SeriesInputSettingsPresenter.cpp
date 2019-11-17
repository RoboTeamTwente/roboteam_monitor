#include "SeriesInputSettingsPresenter.h"
#include "FilterPresenter.h"
#include "../models/FilterModel.h"

// constructor
SeriesInputSettingsPresenter::SeriesInputSettingsPresenter(SeriesInputSettingsModel * model)
    : model(model){ }

void SeriesInputSettingsPresenter::update_channel(const proto::ChannelType & channel_type) {
        model->channel_type = channel_type;
}

std::vector<FilterPresenter *> &SeriesInputSettingsPresenter::get_filters() {
    return model->filters;
}

void SeriesInputSettingsPresenter::add_new_filter() {
    auto empty_filter = new FilterModel(this);
    auto filterPresenter = new FilterPresenter(empty_filter);
    model->filters.emplace_back(filterPresenter);
    emit filterAdded(filterPresenter);
}

void SeriesInputSettingsPresenter::removeFilter(FilterPresenter *filter_to_remove) {
    emit filterRemoved(filter_to_remove);
    model->filters.erase(std::remove(model->filters.begin(), model->filters.end(), filter_to_remove), model->filters.end());
}
proto::ChannelType SeriesInputSettingsPresenter::get_channel_type() const {
    return model->channel_type;
}

// make a snapshot of the presenter and store it as snapshot
void SeriesInputSettingsPresenter::createSnapShot() {
    auto snap = new SeriesInputSettingsModel(* model);
    snapshot = snap;
}

// make the snapshot the presenter
void SeriesInputSettingsPresenter::rollBack() {
    if (snapshot) {
        model = snapshot;
        emit modelChanged();
    } else {
        std::cout << "failed to make snapshot" << std::endl;
    }
}

void SeriesInputSettingsPresenter::confirm() {
    emit finished();
}



