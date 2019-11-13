#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "Chart.h"
#include "ChartSeries.h"

Chart::Chart(QWidget *parent) : QWidget(parent) {
    setMinimumWidth(800);
    setMinimumHeight(600);
    drawView();
    set_theme(true);
}

// Add a new series to the list of series
void Chart::add_new_series() {
    auto series = new ChartSeries("Series " + QString::number(seriesList.size(), 10), this);
    seriesList.push_back(series);
    emit seriesAdded(series);
}

// Remove the series from the list of series
void Chart::delete_series(ChartSeries *series_to_delete) {
    emit seriesRemoved(series_to_delete);
    seriesList.erase(std::remove(seriesList.begin(), seriesList.end(), series_to_delete), seriesList.end());
}

// Allow switching between light and dark theme
void Chart::set_theme(bool dark_theme) {
    this->darkTheme = dark_theme;
    emit themeChanged(dark_theme);
}

// Create all the widgets
void Chart::drawView() {
    auto dialog_horizontal_layout = new QHBoxLayout();
    auto dialog_splitter = new QSplitter();
    setLayout(dialog_horizontal_layout);
    dialog_horizontal_layout->addWidget(dialog_splitter);

    auto series_overview_widget = new QWidget();
    auto series_overview_scroll_layout = new QVBoxLayout();
    auto series_overview_layout = new QVBoxLayout();

    auto scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    auto inner = new QFrame(scroll);

    inner->setLayout(series_overview_layout);
    scroll->setWidget(inner);
    series_overview_scroll_layout->addWidget(scroll);

    series_overview_layout->setAlignment(Qt::AlignTop);

    // add series button
    auto add_series_button = new QPushButton();
    add_series_button->setText("Add series");
    series_overview_layout->addWidget(add_series_button);

    // theme toggle checkbox
    auto theme_checkbox = new QCheckBox("Dark theme");
    theme_checkbox->setChecked(true);
    series_overview_layout->addWidget(theme_checkbox);

    series_overview_widget->setLayout(series_overview_scroll_layout);
    dialog_splitter->addWidget(series_overview_widget);
    series_overview_widget->setMaximumWidth(300);

    // chart
    auto chart = new QChartView();
    chart->chart()->createDefaultAxes();
    chart->chart()->setMinimumHeight(300);
    dialog_splitter->addWidget(chart);

    //////// VIEW --> MODEL CONNECTIONS //////////
    connect(add_series_button, &QPushButton::clicked, this, &Chart::add_new_series);
    connect(theme_checkbox, &QCheckBox::toggled, this, &Chart::set_theme);

    //////// MODEL --> VIEW CONNECTIONS //////////
    connect(this, &Chart::seriesAdded, [series_overview_layout, chart](ChartSeries * series) {
      series_overview_layout->addWidget(series);
      chart->chart()->addSeries(series->get_qt_series());
    });

    connect(this, &Chart::seriesRemoved, [series_overview_layout, chart](ChartSeries * series) {
       series->hide();
       series_overview_layout->removeWidget(series);
       chart->chart()->removeSeries(series->get_qt_series());
    });

    connect(this, &Chart::themeChanged, [chart](bool darkTheme) {
      if (darkTheme) {
          chart->chart()->setTheme(QChart::ChartThemeDark);
          chart->chart()->setBackgroundBrush(QColor(33, 33, 33));
      } else {
          chart->chart()->setTheme(QChart::ChartThemeLight);
          chart->chart()->setBackgroundBrush(QColor(255, 255, 255));
      }
    });
}
#include "include/moc_Chart.cpp"