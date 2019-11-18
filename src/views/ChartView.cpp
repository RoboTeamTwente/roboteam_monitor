#include "ChartView.h"
#include "src/presenters/SeriesPresenter.h"
#include "src/models/SeriesModel.h"

ChartView::ChartView(ChartPresenter *model, QWidget  * parent) : QWidget(parent), presenter(model) {
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

    auto play_pause_button = new QPushButton();
    play_pause_button->setText("Play");
    series_overview_layout->addWidget(play_pause_button);

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
    connect(add_series_button, &QPushButton::clicked, model, &ChartPresenter::add_new_series);
    connect(theme_checkbox, &QCheckBox::toggled, model, &ChartPresenter::set_theme);

    //////// MODEL --> VIEW CONNECTIONS //////////
    connect(model, &ChartPresenter::seriesAdded, [this, series_overview_layout, chart](SeriesPresenter * series_presenter) {

        auto seriesView = new SeriesView(series_presenter);
        seriesMap.insert(std::make_pair(series_presenter, seriesView));

        series_overview_layout->addWidget(seriesView);
        chart->chart()->addSeries(series_presenter->get_qt_series());
        chart->chart()->createDefaultAxes();
    });

    connect(model, &ChartPresenter::seriesRemoved, [this, series_overview_layout, chart](SeriesPresenter * series_presenter) {
       if (auto view = seriesMap.at(series_presenter)) {

           view->hide();
           series_overview_layout->removeWidget(view);
           chart->chart()->removeSeries(series_presenter->get_qt_series());
           chart->chart()->createDefaultAxes();

           seriesMap.erase(series_presenter);
       }
    });

    connect(model, &ChartPresenter::themeChanged, [chart](bool darkTheme) {
      if (darkTheme) {
          chart->chart()->setTheme(QChart::ChartThemeDark);
          chart->chart()->setBackgroundBrush(QColor(33, 33, 33));
      } else {
          chart->chart()->setTheme(QChart::ChartThemeLight);
          chart->chart()->setBackgroundBrush(QColor(255, 255, 255));
      }
    });

}
