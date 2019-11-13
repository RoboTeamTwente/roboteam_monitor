//
// Created by Lukas Bos on 13/11/2019.
//

#include <QVBoxLayout>
#include <QPushButton>
#include <src/models/SeriesModel.h>
#include <src/models/ChartModel.h>

#include "SeriesView.h"
SeriesModel* SeriesView::get_model() const {
    return model;
}
void SeriesView::set_model(SeriesModel* model) {
    SeriesView::model = model;
}

SeriesView::SeriesView(SeriesModel* model, QWidget *parent) : QWidget(parent) {
    set_model(model);
    auto seriesLayout = new QVBoxLayout();
    setLayout(seriesLayout);

    auto removeSeriesBtn = new QPushButton();
    removeSeriesBtn->setText("remove");
    seriesLayout->addWidget(removeSeriesBtn);

    connect(removeSeriesBtn, &QPushButton::clicked, [model]() {
        model->get_parent()->removeSeries(model);
    });
}
