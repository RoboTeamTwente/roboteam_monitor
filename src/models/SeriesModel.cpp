//
// Created by Lukas Bos on 12/11/2019.
//

#include "SeriesModel.h"
#include "../views/components/SeriesView.h"

SeriesModel::SeriesModel(ChartModel *parent) : QObject((QObject *) parent), parent(parent) {
    qt_series = new QSplineSeries();
    setColor(Qt::red);

    srand (time(NULL));

    // dummy data
    qt_series->append(0, rand() % 20 + 1);
    qt_series->append(2, rand() % 20 + 1);
    qt_series->append(4, rand() % 20 + 1);
    qt_series->append(16, rand() % 20 + 1);
}

SeriesModel::SeriesModel(const SeriesModel &other) {

}

ChartModel *SeriesModel::get_parent() const {
    return parent;
}

SeriesModel::~SeriesModel() {}

void SeriesModel::setColor(QColor color) {
     qt_series->setColor(color);
     emit qtSeriesChanged();
}
QColor SeriesModel::getColor() {
    return qt_series->color();
}

QString SeriesModel::getName() {
    return qt_series->name();
}

void SeriesModel::setName(QString name) {
    qt_series->setName(name);
    emit qtSeriesChanged();
}

QXYSeries * SeriesModel::getQtSeries() {
    return qt_series;
}
