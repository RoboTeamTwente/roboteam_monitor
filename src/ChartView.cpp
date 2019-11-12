#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "ChartView.h"
#include "ChartSeries.h"

ChartView::ChartView(QWidget *parent) : QWidget(parent) {
    setMinimumWidth(800);
    setMinimumHeight(600);
    initialize_layout();
    set_theme(true);
}

/*
 * Create the main layout of the ChartView
 */
void ChartView::initialize_layout() {
    auto dialog_horizontal_layout = new QHBoxLayout();
    auto dialog_splitter = new QSplitter();
    setLayout(dialog_horizontal_layout);
    dialog_horizontal_layout->addWidget(dialog_splitter);

    QWidget *series_overview_widget = create_series_overview_widget(dialog_horizontal_layout);

    dialog_splitter->addWidget(series_overview_widget);
    series_overview_widget->setMaximumWidth(300);

    chart = new QChartView();
    chart->chart()->createDefaultAxes();
    chart->chart()->setMinimumHeight(300);
    dialog_splitter->addWidget(chart);
}

/*
 * Create the series overview widget
 * This widget shows all series belonging to the chart
 */
QWidget *ChartView::create_series_overview_widget(QHBoxLayout *dialog_horizontal_layout) {


    auto series_overview_widget = new QWidget();
    auto series_overview_scroll_layout = new QVBoxLayout();
    series_overview_layout = new QVBoxLayout();

    auto scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    auto inner = new QFrame(scroll);

    inner->setLayout(series_overview_layout);
    scroll->setWidget(inner);
    series_overview_scroll_layout->addWidget(scroll);

    series_overview_layout->setAlignment(Qt::AlignTop);

    auto add_series_button = new QPushButton();
    add_series_button->setText("Add series");
    connect(add_series_button, &QPushButton::clicked, this, &ChartView::add_new_series);
    series_overview_layout->addWidget(add_series_button);

    theme_checkbox = new QCheckBox("Dark theme");
    theme_checkbox->setChecked(true);
    series_overview_layout->addWidget(theme_checkbox);

    connect(theme_checkbox, &QCheckBox::toggled, this, &ChartView::set_theme);

    series_overview_widget->setLayout(series_overview_scroll_layout);
    return series_overview_widget;
}

/*
 * Add a new series to the list of series
 */
void ChartView::add_new_series() {
    auto series = new ChartSeries("Series " + QString::number(all_series.size(), 10), this);
    all_series.push_back(series);
    series_overview_layout->addWidget(series);
    chart->chart()->addSeries(series->get_qt_series());
}

/*
 * Remove the series from the list of series
 */
void ChartView::delete_series(ChartSeries *series_to_delete) {
    series_to_delete->hide();
    series_overview_layout->removeWidget(series_to_delete);
    chart->chart()->removeSeries(series_to_delete->get_qt_series());

    // remove from vector
    all_series.erase(std::remove(all_series.begin(), all_series.end(), series_to_delete), all_series.end());
}

/*
 * Allow switching between light and dark theme
 */
void ChartView::set_theme(bool dark_theme) {
    if (dark_theme) {
        chart->chart()->setTheme(QChart::ChartThemeDark);
        chart->chart()->setBackgroundBrush(QColor(33, 33, 33));
    } else {
        chart->chart()->setTheme(QChart::ChartThemeLight);
        chart->chart()->setBackgroundBrush(QColor(255, 255, 255));
    }
}
