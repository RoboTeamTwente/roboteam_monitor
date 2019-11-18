#include "ChartModel.h"

ChartModel::ChartModel() {
    xAxis = new QValueAxis();
    yAxis = new QValueAxis();

    time_chart_created = roboteam_utils::Timer::getCurrentTime().count();
}