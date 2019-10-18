//
// Created by Lukas Bos on 18/10/2019.
//

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "include/ChartView.h"

ChartView::ChartView(QWidget * parent) : QWidget(parent) {
  auto dialog_horizontal_layout = new QHBoxLayout();
  this->setLayout(dialog_horizontal_layout);

  auto series_overview_widget = new QWidget();
  series_overview_layout = new QVBoxLayout();

  auto add_series_button = new QPushButton();
  add_series_button->setText("Add series");
  connect(add_series_button, &QPushButton::clicked, this, &ChartView::add_new_series);
  series_overview_layout->addWidget(add_series_button);
  series_overview_widget->setLayout(series_overview_layout);
  dialog_horizontal_layout->addWidget(series_overview_widget);


  auto chart = new QChartView();

  auto fpsSeries = new QSplineSeries();
  fpsSeries->setUseOpenGL();
  fpsSeries->setColor(Qt::blue);
  fpsSeries->setName("FPS");
  fpsSeries->append(0, 10);
  fpsSeries->append(1, 12);
  fpsSeries->append(2, 8);
  fpsSeries->append(19, 2);

  chart->chart()->addSeries(fpsSeries);
  chart->chart()->createDefaultAxes();
  chart->chart()->setMinimumHeight(300);
  chart->chart()->setTheme(QChart::ChartThemeDark);
  chart->chart()->setBackgroundBrush(QColor(53,53,53));
  chart->chart()->axisY()->setMinorGridLineColor(Qt::gray);
  chart->chart()->axisY()->setGridLineVisible(true);
  chart->chart()->axisY()->setRange(0, 20);
  chart->chart()->axisX()->setRange(0, 20);

  dialog_horizontal_layout->addWidget(chart);
}

void ChartView::add_new_series() {
  auto series = std::make_shared<ChartSeries>(this);
  all_series.push_back(series);
  series_overview_layout->addWidget(series.get());
}

void ChartView::delete_series(ChartSeries * series_to_delete) {
  series_to_delete->hide();
  series_overview_layout->removeWidget(series_to_delete);
}
