#include "ChartView.h"
#include "src/models/SeriesModel.h"

ChartView::ChartView(ChartModel *model, QWidget  * parent) : QWidget(parent), model(model) {
    setMinimumWidth(800);
    setMinimumHeight(600);

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
    chart->chart()->setTheme(QChart::ChartThemeDark);
    chart->chart()->setBackgroundBrush(QColor(33, 33, 33));

    //////// VIEW --> MODEL CONNECTIONS //////////
    connect(add_series_button, &QPushButton::clicked, model, &ChartModel::add_new_series);
    connect(theme_checkbox, &QCheckBox::toggled, model, &ChartModel::set_theme);

    //////// MODEL --> VIEW CONNECTIONS //////////
    connect(model, &ChartModel::seriesAdded, [this, series_overview_layout, chart](SeriesModel * series) {

        auto seriesView = new SeriesView(series);
        seriesMap.insert(std::make_pair(series, seriesView));

        series_overview_layout->addWidget(seriesView);
        chart->chart()->addSeries(series->get_qt_series());
        chart->chart()->createDefaultAxes();
    });

    connect(model, &ChartModel::seriesRemoved, [this, series_overview_layout, chart](SeriesModel * series) {
       if (auto view = seriesMap.at(series)) {

           view->hide();
           series_overview_layout->removeWidget(view);
           chart->chart()->removeSeries(series->get_qt_series());
           chart->chart()->createDefaultAxes();

           seriesMap.erase(series);
       }
    });

    connect(model, &ChartModel::themeChanged, [chart](bool darkTheme) {
      if (darkTheme) {
          chart->chart()->setTheme(QChart::ChartThemeDark);
          chart->chart()->setBackgroundBrush(QColor(33, 33, 33));
      } else {
          chart->chart()->setTheme(QChart::ChartThemeLight);
          chart->chart()->setBackgroundBrush(QColor(255, 255, 255));
      }
    });

}