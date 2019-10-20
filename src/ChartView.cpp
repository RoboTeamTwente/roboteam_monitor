#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "include/ChartView.h"
#include "include/ChartSeries.h"

ChartView::ChartView(QWidget * parent) : QWidget(parent) {

  auto dialog_horizontal_layout = new QHBoxLayout();
  this->setLayout(dialog_horizontal_layout);

  auto dialog_splitter = new QSplitter();
  dialog_horizontal_layout->addWidget(dialog_splitter);

  auto series_overview_widget = new QWidget();
  series_overview_layout = new QVBoxLayout();
  series_overview_layout->setAlignment(Qt::AlignTop);

  auto add_series_button = new QPushButton();
  add_series_button->setText("Add series");
  connect(add_series_button, &QPushButton::clicked, this, &ChartView::add_new_series);
  series_overview_layout->addWidget(add_series_button);

  theme_checkbox = new QCheckBox("Dark theme");
  theme_checkbox->setChecked(true);
  series_overview_layout->addWidget(theme_checkbox);

  connect(theme_checkbox, &QCheckBox::toggled, this, &ChartView::set_theme);

  series_overview_widget->setLayout(series_overview_layout);
  dialog_horizontal_layout->addWidget(series_overview_widget);
  dialog_splitter->addWidget(series_overview_widget);


  chart = new QChartView();
  chart->chart()->createDefaultAxes();
  chart->chart()->setMinimumHeight(300);
  dialog_splitter->addWidget(chart);

  set_theme(true);

}

void ChartView::add_new_series() {
  auto series = new ChartSeries( "Series " + QString::number(all_series.size(), 10), this);
  all_series.push_back(series);
  series_overview_layout->addWidget(series);
  chart->chart()->addSeries(series->get_qt_series());
}

void ChartView::delete_series(ChartSeries * series_to_delete) {
  series_to_delete->hide();
  series_overview_layout->removeWidget(series_to_delete);
  chart->chart()->removeSeries(series_to_delete->get_qt_series());

  // remove from vector
  all_series.erase(std::remove(all_series.begin(), all_series.end(), series_to_delete), all_series.end());
}

void ChartView::set_theme(bool dark_theme) {
  if (dark_theme) {
    chart->chart()->setTheme(QChart::ChartThemeDark);
    chart->chart()->setBackgroundBrush(QColor(33, 33, 33));
  } else {
    chart->chart()->setTheme(QChart::ChartThemeLight);
    chart->chart()->setBackgroundBrush(QColor(255, 255, 255));
  }
}
