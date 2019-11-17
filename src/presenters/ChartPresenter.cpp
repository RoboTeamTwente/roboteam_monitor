#include <src/models/ChartModel.h>
#include "ChartPresenter.h"
#include "SeriesPresenter.h"

ChartPresenter::ChartPresenter(ChartModel *model) : QObject(nullptr), model(model) { }

// Add a new series to the list of series
void ChartPresenter::add_new_series() {
    auto series = new SeriesModel("Series " + QString::number(model->seriesList.size() + 1, 10));
    model->seriesList.push_back(series);
    emit seriesAdded(series);
}

// Remove the series from the list of series
void ChartPresenter::delete_series(SeriesModel *series_to_delete) {
    emit seriesRemoved(series_to_delete);
    auto seriesList = &model->seriesList;
    seriesList->erase(std::remove(seriesList->begin(), seriesList->end(), series_to_delete), seriesList->end());
}

// Allow switching between light and dark theme
void ChartPresenter::set_theme(bool dark_theme) {
    model->darkTheme = dark_theme;
    emit themeChanged(dark_theme);
}
