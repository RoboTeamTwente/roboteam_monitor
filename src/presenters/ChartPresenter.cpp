#include <src/models/ChartModel.h>
#include <src/models/SeriesModel.h>
#include "ChartPresenter.h"
#include "SeriesPresenter.h"

ChartPresenter::ChartPresenter(ChartModel *model, SubscriptionManager *subscription_manager)
: QObject(nullptr), model(model), subscription_manager(subscription_manager) {
init();
}

ChartPresenter::ChartPresenter(json json_data, SubscriptionManager *subscription_manager)
: QObject(nullptr), subscription_manager(subscription_manager){
    model = new ChartModel(this, json_data);
    init();
}

void ChartPresenter::init() {
    xAxis = new QValueAxis();
    yAxis = new QValueAxis();

    auto now = std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::steady_clock::now().time_since_epoch()
    );
    time_chart_created = now.count();
}




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

    /*
     *
     * Here the margins are added. This is to prevent that we have to constantly update the range.
     * This saves a lot of CPU
     *
     */
    if (x < min_x || !has_proper_boundaries) {
        min_x = x - model->margin_x;
    }
    
    if (x > max_x || !has_proper_boundaries) {
        max_x = x + model->margin_x;
    }

    if (y < min_y || !has_proper_boundaries) {
        min_y = y  - model->margin_y;
    }

    if (y > max_y || !has_proper_boundaries) {
        max_y = y  + model->margin_y;
    }
    has_proper_boundaries = true;
}

qreal ChartPresenter::get_min_x() {
    return min_x;
}

qreal ChartPresenter::get_min_y() {
    return min_y;
}

qreal ChartPresenter::get_max_x() {
    return max_x;
}

qreal ChartPresenter::get_max_y() {
    return max_y;
}

QValueAxis *ChartPresenter::getxAxis() {
    return xAxis;
}

QValueAxis *ChartPresenter::getyAxis() {
    return yAxis;
}
void ChartPresenter::setxAxis(QValueAxis * axis) {
    xAxis = axis;
}
void ChartPresenter::setyAxis(QValueAxis * axis) {
    yAxis = axis;
}

long ChartPresenter::get_time_chart_created() {
    return time_chart_created;
}

std::vector<SeriesPresenter *> ChartPresenter::get_series_list() {
    return model->seriesList;
}
bool ChartPresenter::is_sliding_window() const {
    return model->sliding_window;
}
void ChartPresenter::set_sliding_window(bool sliding_window) {
    model->sliding_window = sliding_window;
    emit set_sliding_window_changed(sliding_window);
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

void ChartPresenter::resetBoundaries() {
    min_x = 1;
    max_x = 0;
    min_y = 1;
    max_y = 0;
    has_proper_boundaries = false;
}
void ChartPresenter::apply_data() {

    for (auto series : get_series_list()) {
        series->apply_data();
    }

        // apply the boundaries
    if (is_sliding_window()) {
        getxAxis()->setMin(get_max_x() - get_sliding_window_width());
        getxAxis()->setMax(get_max_x() + get_margin_x());
    } else {
        getxAxis()->setMin(get_min_x() - get_margin_x());
        getxAxis()->setMax(get_max_x() + get_margin_x());
    }
    getyAxis()->setMin(get_min_y() - get_margin_y());
    getyAxis()->setMax(get_max_y() + get_margin_y());
}

void ChartPresenter::clear_data() {
    for (auto series : get_series_list()) {
        series->clear_data();
    }
}

json ChartPresenter::to_json() {
    return model->to_json();
}
bool ChartPresenter::is_dark_theme() {
    return model->darkTheme;
}
void ChartPresenter::update_ip_config(const QString & ip) {
    model->ip_config = ip;
    subscription_manager->reconfigure_ip(ip);
}
QString ChartPresenter::get_ip_config() {
    return model->ip_config;
}
SubscriptionManager *ChartPresenter::get_subscription_manager() const {
    return subscription_manager;
}



