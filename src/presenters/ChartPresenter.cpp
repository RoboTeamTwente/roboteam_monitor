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
}

// Allow switching between light and dark theme
void ChartPresenter::set_theme(bool dark_theme) {
    model->darkTheme = dark_theme;
    emit themeChanged(dark_theme);
}

// change boundaries of chart if necessary
void ChartPresenter::adjustBoundaries(const qreal & x, const qreal & y) {
    double margin_y = 0.05; // 5 % above and under the graph
    if (x < model->min_x) {

        model->min_x = x;
        model->xAxis->setMin(model->max_x - 10);
    }
    
    if (x > model->max_x) {
        model->max_x = x;
        model->xAxis->setMax(x);
        model->xAxis->setMin(model->max_x - 10);

    }

    if (y < model->min_y) {
        model->min_y = y;
        model->yAxis->setMin(y-y*margin_y);
    }

    if (y > model->max_y) {
        model->max_y = y;
        model->yAxis->setMax(y+y*margin_y);
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


