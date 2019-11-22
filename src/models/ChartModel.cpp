#include "ChartModel.h"
#include "SeriesModel.h"

ChartModel::ChartModel() {
    xAxis = new QValueAxis();
    yAxis = new QValueAxis();

    auto now = std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::steady_clock::now().time_since_epoch()
    );
    time_chart_created = now.count();
}

ChartModel::ChartModel(ChartPresenter * presenter, json data) {
    xAxis = new QValueAxis();
    yAxis = new QValueAxis();

    auto now = std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::steady_clock::now().time_since_epoch()
    );
    time_chart_created = now.count();

    darkTheme = data.value("dark_theme", darkTheme);
    sliding_window = data.value("sliding_window", sliding_window);
    sliding_window_width = data.value("sliding_window_width", sliding_window_width);
    margin_y = data.value("margin_y", margin_y);
    margin_x = data.value("margin_x", margin_x);
    ip_config = QString::fromStdString(data.value("ip_config", ip_config.toStdString()));

    update_frequency = data.value("update_frequency", update_frequency);

    for (auto const & series_json : data["series_list"]) {
        auto series_model = new SeriesModel(presenter, series_json);
        auto series_presenter = new SeriesPresenter(series_model);
        seriesList.push_back(series_presenter);
    }

}

json ChartModel::to_json() {
    // convert the vector of seriesPresenter* to seriesmodel jsons
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
