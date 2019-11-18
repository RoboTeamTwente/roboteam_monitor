#include <src/utils/Helpers.h>
#include "SeriesSettingsPresenter.h"
#include "FilterPresenter.h"
#include "../models/FilterModel.h"

// constructor
SeriesSettingsPresenter::SeriesSettingsPresenter(SeriesSettingsModel * model)
    : model(model){

    // We have to remove all filters when the channel changes
    connect(this, &SeriesSettingsPresenter::channelChanged, [this, model]() {
      for (auto filter : model->filters) {
          removeFilter(filter);
      }
    });
}

void SeriesSettingsPresenter::update_channel(const proto::ChannelType & channel_type) {
        model->channel_type = channel_type;
        emit channelChanged(channel_type);
}

std::vector<FilterPresenter *> &SeriesSettingsPresenter::get_filters() {
    return model->filters;
}

void SeriesSettingsPresenter::add_new_filter() {
    auto empty_filter = new FilterModel(this);
    auto filterPresenter = new FilterPresenter(empty_filter);
    model->filters.emplace_back(filterPresenter);
    emit filterAdded(filterPresenter);
}

void SeriesSettingsPresenter::removeFilter(FilterPresenter *filter_to_remove) {
    emit filterRemoved(filter_to_remove);
    model->filters.erase(std::remove(model->filters.begin(), model->filters.end(), filter_to_remove), model->filters.end());
}
proto::ChannelType SeriesSettingsPresenter::get_channel_type() const {
    return model->channel_type;
}

// make a snapshot of the presenter and store it as snapshot
void SeriesSettingsPresenter::createSnapShot() {
    std::cout << "[SeriesSettingsPresenter] Creating snapshot..." << std::endl;
    auto snap = new SeriesSettingsModel(* model);
    snapshot = snap;
}

// make the snapshot the presenter
void SeriesSettingsPresenter::rollBack() {
    if (snapshot) {
        model = snapshot;
        emit modelChanged();
    } else {
        std::cout << "failed to make snapshot" << std::endl;
    }
}

void SeriesSettingsPresenter::confirm() {
    snapshot = model;
    emit finished();
}

bool SeriesSettingsPresenter::is_dirty() {
    return snapshot && (*snapshot != *model);
}

void SeriesSettingsPresenter::update_channel(const QString &channel_str) {
    update_channel(Helpers::getChannelTypeByName(channel_str));
}





