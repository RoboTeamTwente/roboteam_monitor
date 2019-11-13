//
// Created by Lukas Bos on 12/11/2019.
//

#include "ChartModel.h"

ChartModel::ChartModel(QObject * parent) : QObject(parent){ }

void ChartModel::addSeries(SeriesModel* series) {
    this->series_list.push_back(series);
    emit seriesChanged();
}

void ChartModel::setDarkTheme(bool dark_theme) {
    this->dark_theme = dark_theme;
    emit themeChanged();
}

void ChartModel::removeSeries(SeriesModel* series) {
    series_list.erase(std::remove(series_list.begin(), series_list.end(), series), series_list.end());
    emit seriesChanged();
}

bool ChartModel::is_dark_theme() {
    return dark_theme;
}

void ChartModel::add_new_series() {
    auto new_series_model = new SeriesModel(this);
    new_series_model->setName("test");
    addSeries(new_series_model);
}

std::vector<SeriesModel*> ChartModel::get_series_list() {
    return series_list;
}


