#include <src/utils/Helpers.h>
#include "SeriesSettingsPresenter.h"
#include "FilterPresenter.h"
#include "../models/FilterModel.h"

// Constructor
// This also sets up some internal signals
SeriesSettingsPresenter::SeriesSettingsPresenter(SeriesSettingsModel * model)
    : model(model){

    // We have to remove all filters when the channel changes
    connect(this, &SeriesSettingsPresenter::channelChanged, this, &SeriesSettingsPresenter::removeAllFilters);
}

// Update the channel with a channel type
void SeriesSettingsPresenter::update_channel(const proto::ChannelType & channel_type) {
        model->channel_type = channel_type;
        emit channelChanged(channel_type);
}

// Return all filters of the model
std::vector<FilterPresenter *> &SeriesSettingsPresenter::get_filters() {
    return model->filters;
}

// Add a new filter to the list of filters
void SeriesSettingsPresenter::add_new_filter() {
    auto empty_filter = new FilterModel(this);
    auto filterPresenter = new FilterPresenter(empty_filter);
    model->filters.emplace_back(filterPresenter);
    emit filterAdded(filterPresenter);
}

// Remove a specified filter
void SeriesSettingsPresenter::removeFilter(FilterPresenter *filter_to_remove) {
    emit filterRemoved(filter_to_remove);
    model->filters.erase(std::remove(model->filters.begin(), model->filters.end(), filter_to_remove), model->filters.end());
}

// Return the currently selected channel type
proto::ChannelType SeriesSettingsPresenter::get_channel_type() const {
    return model->channel_type;
}

// make a snapshot of the presenter and store it as snapshot
void SeriesSettingsPresenter::createSnapShot() {
    std::cout << "[SeriesSettingsPresenter] Creating snapshot..." << std::endl;
    auto snap = new SeriesSettingsModel(* model);
    snapshot = snap;
}

// Make the snapshot the presenter
void SeriesSettingsPresenter::rollBack() {
    if (snapshot) {
        model = snapshot;
        emit modelChanged();
    } else {
        std::cout << "failed to make snapshot" << std::endl;
    }
}

// Confirm the changes
void SeriesSettingsPresenter::confirm() {
    snapshot = model;
    emit finished();
}

// If the model is different from the snapshot (i.e. it has unsaved changes), it is considered 'dirty'.
bool SeriesSettingsPresenter::is_dirty() {
    return snapshot && (*snapshot != *model);
}

// Update the channel from a QString
void SeriesSettingsPresenter::update_channel(const QString &channel_str) {
    update_channel(Helpers::getChannelTypeByName(channel_str));
}

// Either use the packet rate or a custom field
void SeriesSettingsPresenter::set_use_packet_rate(bool use_packet_rate) {
    model->use_packet_rate = use_packet_rate;
    emit rateSettingChanged(use_packet_rate);
}

// return if we use a packet rate or not.
bool SeriesSettingsPresenter::use_packet_rate() {
    return model->use_packet_rate;
}
void SeriesSettingsPresenter::removeAllFilters() {
    for (auto filter : model->filters) {
        removeFilter(filter);
    }
}





