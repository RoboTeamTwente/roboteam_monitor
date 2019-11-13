#include <QHBoxLayout>
#include <QPushButton>
#include <src/utilities/Helpers.h>
#include "ChartView.h"
#include "src/models/ChartSeries.h"
#include "SeriesView.h"

ChartView::ChartView(ChartModel * model, QWidget *parent) : QWidget(parent) {
    setMinimumWidth(800);
    setMinimumHeight(600);

    auto dialog_horizontal_layout = new QHBoxLayout();
    setLayout(dialog_horizontal_layout);


    auto dialog_splitter = new QSplitter();
    dialog_horizontal_layout->addWidget(dialog_splitter);

    auto series_list_widget = new QWidget();
    auto series_list_layout = new QVBoxLayout();
    series_list_widget->setLayout(series_list_layout);

    auto new_series_btn = new QPushButton();
    new_series_btn->setText("Add series");
    series_list_layout->addWidget(new_series_btn);
    connect(new_series_btn, &QPushButton::clicked, model, &ChartModel::add_new_series);

    auto series_list_container = new QVBoxLayout();
    series_list_layout->addLayout(series_list_container);
    series_list_layout->setAlignment(Qt::AlignTop);

    auto chart = new QChartView();
    chart->chart()->createDefaultAxes();
    chart->chart()->setMinimumHeight(300);
    dialog_splitter->addWidget(chart);

    // when the series change reload the views:
    connect(model, &ChartModel::seriesChanged, [model, series_list_container, chart]() {
        Helpers::clearLayout(series_list_container);

        for (auto series : model->get_series_list()) {
            auto seriesView = new SeriesView(series);
            series_list_container->addWidget(seriesView);
        }


        chart->chart()->removeAllSeries();
        for (auto series : model->get_series_list()) {
        //    chart->chart()->addSeries(series->getQtSeries());
            chart->chart()->createDefaultAxes();
        }
    });
    dialog_splitter->addWidget(series_list_widget);
}


