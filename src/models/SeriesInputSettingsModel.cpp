#include "SeriesInputSettingsModel.h"

std::vector<FilterPresenter * > SeriesInputSettingsModel::get_filters() {
    return filters;
}

void SeriesInputSettingsModel::set_filters(const std::vector<FilterPresenter *> &filters) {
    SeriesInputSettingsModel::filters = filters;
}

proto::ChannelType SeriesInputSettingsModel::get_channel_type() const {
    return channel_type;
}

void SeriesInputSettingsModel::set_channel_type(proto::ChannelType channel_type) {
    SeriesInputSettingsModel::channel_type = channel_type;
}

SeriesPresenter *SeriesInputSettingsModel::get_parent() const {
    return parent;
}

void SeriesInputSettingsModel::set_parent(SeriesPresenter *parent) {
    SeriesInputSettingsModel::parent = parent;
}
