#include "ChartModel.h"
#include "SeriesModel.h"

// Create a chart model from JSON.
// If a property is not present in JSON, it will use the default values.
ChartModel::ChartModel(ChartPresenter * presenter, json data) {
    // properties
    darkTheme = data.value("dark_theme", darkTheme);
    sliding_window = data.value("sliding_window", sliding_window);
    sliding_window_width = data.value("sliding_window_width", sliding_window_width);
    margin_y = data.value("margin_y", margin_y);
    margin_x = data.value("margin_x", margin_x);
    ip_config = QString::fromStdString(data.value("ip_config", ip_config.toStdString()));
    update_frequency = data.value("update_frequency", update_frequency);

    // child objects
    for (auto const & series_json : data["series_list"]) {
        auto series_model = new SeriesModel(presenter, series_json);
        auto series_presenter = new SeriesPresenter(series_model);
        seriesList.push_back(series_presenter);
    }
}

// Generate a JSON object from the model
json ChartModel::to_json() {
    std::vector<json> series_jsons;
    series_jsons.reserve(seriesList.size());

    for (auto series_presenter : seriesList) {
        series_jsons.push_back(series_presenter->to_json());
    }

    return {
        {"dark_theme", darkTheme},
        {"sliding_window", sliding_window},
        {"sliding_window_width", sliding_window_width},
        {"margin_y", margin_y},
        {"margin_x", margin_x},
        {"update_frequency", update_frequency},
        {"series_list", series_jsons},
        {"ip_config", ip_config.toStdString()}
    };
}
