#include <src/models/ChartModel.h>
#include "ChartPresenter.h"
#include "SeriesPresenter.h"

ChartPresenter::ChartPresenter(ChartModel *model) : QObject(nullptr), model(model) { }

// Add a new series to the list of series
void ChartPresenter::add_new_series() {
    auto series = new SeriesModel(this, "Series " + QString::number(model->seriesList.size() + 1, 10));
    auto presenter = new SeriesPresenter(series);
    model->seriesList.push_back(presenter);
    emit seriesAdded(presenter);
}

// Remove the series from the list of series
void ChartPresenter::delete_series(SeriesPresenter *series_to_delete) {
    emit seriesRemoved(series_to_delete);
    auto seriesList = &model->seriesList;
    seriesList->erase(std::remove(seriesList->begin(), seriesList->end(), series_to_delete), seriesList->end());
    delete series_to_delete;
}

// Allow switching between light and dark theme
void ChartPresenter::set_theme(bool dark_theme) {
    model->darkTheme = dark_theme;
    emit themeChanged(dark_theme);
}

// change boundaries of chart if necessary
void ChartPresenter::adjustBoundaries(const qreal & x, const qreal & y, const qreal & margin) {
    double margin_y = 0.05; // 5 % above and under the graph
    if (x < model->min_x) {

        model->min_x = x;
       // model->xAxis->setMin(model->max_x - margin);
    }
    
    if (x > model->max_x) {
        model->max_x = x;
     //   model->xAxis->setMax(x);
       // model->xAxis->setMin(model->max_x - margin);

    }

    if (y < model->min_y) {
        model->min_y = y;
       // model->yAxis->setMin(y-y*margin_y);
    }

    if (y > model->max_y) {
        model->max_y = y;
       // model->yAxis->setMax(y+y*margin_y);
    }
}

qreal ChartPresenter::get_min_x() {
    return model->min_x;
}

qreal ChartPresenter::get_min_y() {
    return model->min_y;
}

qreal ChartPresenter::get_max_x() {
    return model->max_x;
}

qreal ChartPresenter::get_max_y() {
    return model->max_y;
}

QValueAxis *ChartPresenter::getxAxis() {
    return model->xAxis;
}

QValueAxis *ChartPresenter::getyAxis() {
    return model->yAxis;
}
void ChartPresenter::setxAxis(QValueAxis * axis) {
    model->xAxis = axis;
}
void ChartPresenter::setyAxis(QValueAxis * axis) {
    model->yAxis = axis;

}

long ChartPresenter::get_time_chart_created() {
    return model->time_chart_created;
}

std::vector<SeriesPresenter *> ChartPresenter::get_series_list() {
    return model->seriesList;
}
bool ChartPresenter::is_sliding_window() const {
    return model->sliding_window;
}
void ChartPresenter::set_sliding_window(bool sliding_window) {
    model->sliding_window = sliding_window;
}
qreal ChartPresenter::get_sliding_window_width() const {
    return model->sliding_window_width;
}
void ChartPresenter::set_sliding_window_width(qreal sliding_window_width) {
    model->sliding_window_width = sliding_window_width;
}
qreal ChartPresenter::get_margin_y() const {
    return model->margin_y;
}
void ChartPresenter::set_margin_y(qreal margin_y) {
    model->margin_y = margin_y;
}
qreal ChartPresenter::get_margin_x() const {
    return model->margin_x;
}
void ChartPresenter::set_margin_x(qreal margin_x) {
    model->margin_x = margin_x;
}
int ChartPresenter::get_update_frequency() const {
    return model->update_frequency;
}
void ChartPresenter::set_update_frequency(int update_frequency) {
    model->update_frequency = update_frequency;
    emit update_frequency_changed(update_frequency);
}


