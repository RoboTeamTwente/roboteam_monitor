#include "SeriesModel.h"
#include "SeriesSettingsModel.h"
#include <src/utils/Helpers.h>
#include <src/presenters/SeriesSettingsPresenter.h>

using namespace google::protobuf;

SeriesModel::SeriesModel(ChartPresenter * parent, const QString & name): parent(parent) {
    auto settings = new SeriesSettingsModel(new SeriesPresenter(this));
    settings_presenter = new SeriesSettingsPresenter(settings);
}

SeriesModel::SeriesModel(ChartPresenter *parent, json json_data) : parent(parent) {
    auto json_name = json_data.value("name", "Series");
    json json_settings = json_data["settings"];

    SeriesSettingsModel * settings;
    if (!json_settings.is_null()) {
        auto series_presenter = new SeriesPresenter(this);
        settings = new SeriesSettingsModel(series_presenter, json_settings);
    } else {
        settings = new SeriesSettingsModel(new SeriesPresenter(this));
    }
    settings_presenter = new SeriesSettingsPresenter(settings);
}

ChartPresenter *SeriesModel::get_parent() const {
    return parent;
}

json SeriesModel::to_json() {
    return {
        {"name", "series_name"},
        {"settings", settings_presenter->get_model_copy()->to_json()}
    };
}



