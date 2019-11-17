#include "SeriesInputSettingsPresenter.h"
#include "src/models/FilterModel.h"

// constructor
SeriesInputSettingsPresenter::SeriesInputSettingsPresenter(SeriesInputSettingsModel * model)
    : model(model){ }

void SeriesInputSettingsPresenter::update_channel(const proto::ChannelType & channel_type) {
        model->channel_type = channel_type;
}

const std::vector<FilterModel> &SeriesInputSettingsPresenter::get_filters() const {
    return model->filters;
}

void SeriesInputSettingsPresenter::add_new_filter() {
    FilterModel empty_filter;
    model->filters.emplace_back(std::move(empty_filter));
    emit filterAdded(&model->filters.back());
}

void SeriesInputSettingsPresenter::removeFilter(FilterModel *filter_to_remove) {
    emit filterRemoved(filter_to_remove);
    model->filters.erase(std::remove(model->filters.begin(), model->filters.end(), *filter_to_remove), model->filters.end());
}
proto::ChannelType SeriesInputSettingsPresenter::get_channel_type() const {
    return model->channel_type;
}

SeriesInputSettingsModel * SeriesInputSettingsPresenter::get_model() const {
    return model;
}

// make a snapshot of the model and store it as snapshot
void SeriesInputSettingsPresenter::createSnapShot() {
    auto snap = new SeriesInputSettingsModel(* model);
    snapshot = snap;
}

// make the snapshot the model
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



