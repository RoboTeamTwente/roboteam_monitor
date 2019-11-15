//
// Created by Lukas Bos on 15/11/2019.
//

#include "SeriesInputSettingsModel.h"
#include "FilterModel.h"


SeriesInputSettingsModel::SeriesInputSettingsModel(const SeriesInputSettingsModel &other) {
    channel_type = other.channel_type;

    for (auto filter : other.get_filters()) {
        filters.push_back(filter->clone());
    }
}

void SeriesInputSettingsModel::update_channel(const proto::ChannelType & channel_type) {
    if (this->channel_type != channel_type) {
        this->channel_type = channel_type;
     //   init_subscriber_for_channel_type(channel_type);
    }
}

const std::vector<FilterModel *> &SeriesInputSettingsModel::get_filters() const {
    return filters;
}

void SeriesInputSettingsModel::add_new_filter() {
    auto empty_filter = new FilterModel();
    filters.push_back(empty_filter);
    emit filterAdded(empty_filter);
}

void SeriesInputSettingsModel::removeFilter(FilterModel *filter_to_remove) {
    emit filterRemoved(filter_to_remove);
    filters.erase(std::remove(filters.begin(), filters.end(), filter_to_remove), filters.end());
}
proto::ChannelType SeriesInputSettingsModel::get_channel_type() const {
    return channel_type;
}


