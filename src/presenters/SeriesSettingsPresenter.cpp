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
    get_internal_model()->channel_type = channel_type;
    emit channelChanged(channel_type);
}

// Return all filters of the model
std::vector<FilterPresenter *> &SeriesSettingsPresenter::get_filters() {
    return get_internal_model()->filters;
}

// Add a new filter to the list of filters
void SeriesSettingsPresenter::add_new_filter() {
    auto empty_filter = new FilterModel(this);
    auto filterPresenter = new FilterPresenter(empty_filter);
    get_internal_model()->filters.emplace_back(filterPresenter);
    emit filterAdded(filterPresenter);
}

// Remove a specified filter
void SeriesSettingsPresenter::removeFilter(FilterPresenter *filter_to_remove) {
    emit filterRemoved(filter_to_remove);
    auto m = get_internal_model();
    m->filters.erase(std::remove(m->filters.begin(), m->filters.end(), filter_to_remove), m->filters.end());
}

// Return the currently selected channel type
proto::ChannelType SeriesSettingsPresenter::get_channel_type() {
    return get_internal_model()->channel_type;
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
        snapshot = model;
    } else {
        std::cout << "failed to rollback snapshot" << std::endl;
    }
}

// Confirm the changes and boot up the new subscriber for the series
void SeriesSettingsPresenter::confirm() {
    emit modelChanged();
    model->parent->start_new_subscription();
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
    get_internal_model()->use_packet_rate = use_packet_rate;
    emit rateSettingChanged(use_packet_rate);
}

// return if we use a packet rate or not.
bool SeriesSettingsPresenter::use_packet_rate() {
    return get_internal_model()->use_packet_rate;
}

// Remove all the filters.
// The following implementation was chosen to also update the gui as well.
void SeriesSettingsPresenter::removeAllFilters() {
    for (auto filter : get_internal_model()->filters) {
        removeFilter(filter);
    }
}

void SeriesSettingsPresenter::set_field_to_show(FieldDefinition * field_definition) {
    model->field_to_show = field_definition;
    emit field_to_show_changed(field_definition);
}

FieldDefinition *SeriesSettingsPresenter::get_field_to_show() {
    return get_internal_model()->field_to_show;
}

SeriesSettingsModel *SeriesSettingsPresenter::get_internal_model() {
    return model;
}

SeriesSettingsModel *SeriesSettingsPresenter::get_model_copy() const {
    return new SeriesSettingsModel(*model);
}


bool SeriesSettingsPresenter::is_valid() {

    for (auto filter : model->filters) {
        if (!filter->is_valid()) return false;
    }

    // the values have to be defined
    return model->channel_type != proto::ChannelType::UNDEFINED_CHANNEL && (use_packet_rate() || model->field_to_show);
}

json SeriesSettingsPresenter::to_json() {
    return model->to_json();
}








