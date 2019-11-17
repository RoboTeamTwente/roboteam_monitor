#include "ChartModel.h"

ChartModel::ChartModel() {}

bool ChartModel::is_dark_theme() const {
    return darkTheme;
}
void ChartModel::set_dark_theme(bool dark_theme) {
    darkTheme = dark_theme;
}
const std::vector<SeriesModel *> &ChartModel::get_series_list() const {
    return seriesList;
}
void ChartModel::set_series_list(const std::vector<SeriesModel *> &series_list) {
    seriesList = series_list;
}
