#include "ChartModel.h"

ChartModel::ChartModel() {
    xAxis = new QValueAxis();
    yAxis = new QValueAxis();
    time_chart_created = roboteam_utils::Timer::getCurrentTime().count();
}

json ChartModel::to_json() {
    // convert the vector of seriesPresenter* to seriesmodel jsons
    std::vector<json> series_jsons;
    series_jsons.reserve(seriesList.size());

    for (auto series_presenter : seriesList) {
        series_jsons.push_back(series_presenter->to_json());
    }

    return {
        {"model", "chart"},
        {"attributes", {
            {"dark_theme", darkTheme},
            {"sliding_window", sliding_window},
            {"sliding_window_width", sliding_window_width},
            {"margin_y", margin_y},
            {"margin_x", margin_x},
            {"update_frequency", update_frequency},
            {"series_list", series_jsons}
        }}
    };
}
