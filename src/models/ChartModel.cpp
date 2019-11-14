#include "models/ChartModel.h"
#include "include/models/SeriesModel.h"

ChartModel::ChartModel() : QObject(nullptr) { }

// Add a new series to the list of series
void ChartModel::add_new_series() {
    auto series = new SeriesModel(this);
    seriesList.push_back(series);
    emit seriesAdded(series);
}

// Remove the series from the list of series
void ChartModel::delete_series(SeriesModel *series_to_delete) {
    emit seriesRemoved(series_to_delete);
    seriesList.erase(std::remove(seriesList.begin(), seriesList.end(), series_to_delete), seriesList.end());
}

// Allow switching between light and dark theme
void ChartModel::set_theme(bool dark_theme) {
    this->darkTheme = dark_theme;
    emit themeChanged(dark_theme);
}


#include "include/models/moc_ChartModel.cpp"