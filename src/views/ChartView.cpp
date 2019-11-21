#include "ChartView.h"
#include "src/presenters/SeriesPresenter.h"
#include "src/models/SeriesModel.h"
#include <QSpinBox>

ChartView::ChartView(ChartPresenter *presenter, QWidget  * parent) : QWidget(parent), presenter(presenter) {
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
    auto add_series_button = new QPushButton(this);
    add_series_button->setText("Add series");
    series_overview_layout->addWidget(add_series_button);

    auto group = new QGroupBox();

    auto g_layout = new QFormLayout();
    group->setLayout(g_layout);


    auto margin_y_spinbox = new QSpinBox(this);
    margin_y_spinbox->setRange(0, 9e99);
    g_layout->addRow(new QLabel("Margin y"), margin_y_spinbox);

    auto sliding_window_checkbox = new QCheckBox(this);
    g_layout->addRow(new QLabel("Sliding window"), sliding_window_checkbox);

    auto sliding_window_margin = new QSpinBox(this);
    sliding_window_margin->setRange(0, 9e99);
    g_layout->addRow(new QLabel("Sliding window margin"), sliding_window_margin);

    auto update_frequency_spin = new QSpinBox(this);
    update_frequency_spin->setRange(1, 100);
    update_frequency_spin->setValue(presenter->get_update_frequency());
    g_layout->addRow(new QLabel("Chart update frequency (Hz)"), update_frequency_spin);
    connect(update_frequency_spin, &QSpinBox::editingFinished, [presenter, update_frequency_spin]() {
      presenter->set_update_frequency(update_frequency_spin->value());
    });

    // theme toggle checkbox
    auto theme_checkbox = new QCheckBox();
    theme_checkbox->setChecked(true);
    g_layout->addRow(new QLabel("Dark theme"), theme_checkbox);
    connect(theme_checkbox, &QCheckBox::toggled, presenter, &ChartPresenter::set_theme);

    series_overview_layout->addWidget(group);

    series_overview_widget->setLayout(series_overview_scroll_layout);
    dialog_splitter->addWidget(series_overview_widget);
    series_overview_widget->setMaximumWidth(300);

    // chart
    auto chart = new QChartView();
    chart->chart()->setMinimumHeight(300);
    dialog_splitter->addWidget(chart);
    chart->chart()->setTheme(QChart::ChartThemeDark);
    chart->chart()->setBackgroundBrush(QColor(33, 33, 33));
    chart->setRenderHint(QPainter::Antialiasing);
    chart->chart()->createDefaultAxes();

    chart->chart()->addAxis(presenter->getxAxis(), Qt::AlignBottom);
    chart->chart()->addAxis(presenter->getyAxis(), Qt::AlignLeft);

    presenter->getxAxis()->setTitleText("Time");
    presenter->getyAxis()->setTitleText("Rate");

    presenter->getxAxis()->setRange(0, 10);
    presenter->getyAxis()->setRange(0,10);

    presenter->getxAxis()->setTickCount(10);
    presenter->getyAxis()->setTickCount(10);

//    presenter->setxAxis(dynamic_cast<QValueAxis *>(chart->chart()->axes(Qt::Horizontal)[0]));
//    presenter->setyAxis(dynamic_cast<QValueAxis *>(chart->chart()->axes(Qt::Vertical)[0]));
    chart->chart()->addAxis(presenter->getxAxis(), Qt::AlignBottom);
    chart->chart()->addAxis(presenter->getyAxis(), Qt::AlignLeft);


    auto timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [presenter]() {
         for (auto series : presenter->get_series_list()) {
             series->apply_data();
         }
    });
    timer->start(presenter->get_update_frequency());

    connect(presenter, &ChartPresenter::update_frequency_changed, [timer](int frequency) {
       timer->stop();
       timer->start((1.0/(double)frequency)*1000.0);
    });

    //////// VIEW --> MODEL CONNECTIONS //////////
    connect(add_series_button, &QPushButton::clicked, presenter, &ChartPresenter::add_new_series);
    connect(theme_checkbox, &QCheckBox::toggled, presenter, &ChartPresenter::set_theme);

    //////// MODEL --> VIEW CONNECTIONS //////////
    connect(presenter, &ChartPresenter::seriesAdded, [this, series_overview_layout, chart, presenter](SeriesPresenter * series_presenter) {
        auto seriesView = new SeriesView(series_presenter);
        seriesMap.insert(std::make_pair(series_presenter, seriesView));
        series_overview_layout->addWidget(seriesView);
        chart->chart()->addSeries(series_presenter->get_qt_series());

      series_presenter->get_qt_series()->attachAxis(series_presenter->getParent()->getxAxis());
      series_presenter->get_qt_series()->attachAxis(series_presenter->getParent()->getyAxis());
    });

    connect(presenter, &ChartPresenter::seriesRemoved, [this, series_overview_layout, chart](SeriesPresenter * series_presenter) {
       if (auto view = seriesMap.at(series_presenter)) {
           view->hide();
           series_overview_layout->removeWidget(view);
           chart->chart()->removeSeries(series_presenter->get_qt_series());
           // chart->chart()->createDefaultAxes();
           seriesMap.erase(series_presenter);
       }
    });

    connect(presenter, &ChartPresenter::themeChanged, [chart](bool darkTheme) {
      if (darkTheme) {
          chart->chart()->setTheme(QChart::ChartThemeDark);
          chart->chart()->setBackgroundBrush(QColor(33, 33, 33));
      } else {
          chart->chart()->setTheme(QChart::ChartThemeLight);
          chart->chart()->setBackgroundBrush(QColor(255, 255, 255));
      }
    });

}
