#include "ChartView.h"
#include "src/presenters/SeriesPresenter.h"
#include "src/models/SeriesModel.h"
#include <QSpinBox>
#include <src/utils/Helpers.h>
#include <QDoubleSpinBox>

ChartView::ChartView(ChartPresenter *presenter, QWidget *parent) : QWidget(parent), presenter(presenter) {
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

    auto margin_y_spinbox = new QDoubleSpinBox(this);
    margin_y_spinbox->setFixedWidth(100);
    margin_y_spinbox->setRange(0, 9e99);
    margin_y_spinbox->setValue(presenter->get_margin_y());
    g_layout->addRow(new QLabel("Margin y"), margin_y_spinbox);
    connect(margin_y_spinbox, SIGNAL(valueChanged(double)), presenter, SLOT(set_margin_y(double)));

    auto margin_x_spinbox = new QDoubleSpinBox(this);
    margin_x_spinbox->setFixedWidth(100);
    margin_x_spinbox->setRange(0, 9e99);
    margin_x_spinbox->setValue(presenter->get_margin_x());
    g_layout->addRow(new QLabel("Margin x"), margin_x_spinbox);
    connect(margin_x_spinbox, SIGNAL(valueChanged(double)), presenter, SLOT(set_margin_x(double)));

    auto sliding_window_checkbox = new QCheckBox(this);
    g_layout->addRow(new QLabel("Sliding window"), sliding_window_checkbox);
    sliding_window_checkbox->setChecked(presenter->is_sliding_window());
    connect(sliding_window_checkbox, &QCheckBox::toggled, presenter, &ChartPresenter::set_sliding_window);

    auto sliding_window_margin = new QDoubleSpinBox(this);
    sliding_window_margin->setFixedWidth(100);
    sliding_window_margin->setValue(presenter->get_sliding_window_width());
    sliding_window_margin->setRange(0, 9e99);
    g_layout->addRow(new QLabel("Sliding window margin"), sliding_window_margin);
    connect(sliding_window_margin, SIGNAL(valueChanged(double)), presenter, SLOT(set_sliding_window_width(double)));
    connect(presenter, &ChartPresenter::set_sliding_window_changed, [sliding_window_margin](bool enabled) {
      sliding_window_margin->setEnabled(enabled);
      if (enabled) {
          sliding_window_margin->setStyleSheet("background-color: auto;");
      } else {
          sliding_window_margin->setStyleSheet("background-color: gray;");
      }
    });

    sliding_window_margin->setEnabled(presenter->is_sliding_window());
    if (presenter->is_sliding_window()) {
        sliding_window_margin->setStyleSheet("background-color: auto;");
    } else {
        sliding_window_margin->setStyleSheet("background-color: gray;");
    }

    auto update_frequency_spin = new QSpinBox(this);
    update_frequency_spin->setFixedWidth(100);
    update_frequency_spin->setRange(1, 100);
    update_frequency_spin->setValue(presenter->get_update_frequency());
    g_layout->addRow(new QLabel("Chart update frequency (Hz)"), update_frequency_spin);

    //somehow this breaks with new syntax
    connect(update_frequency_spin, SIGNAL(valueChanged(int)), presenter, SLOT(set_update_frequency(int)));

    // theme toggle checkbox
    auto theme_checkbox = new QCheckBox();
    theme_checkbox->setChecked(presenter->is_dark_theme());
    g_layout->addRow(new QLabel("Dark theme"), theme_checkbox);

    connect(theme_checkbox, &QCheckBox::toggled, presenter, &ChartPresenter::set_theme);

    auto reset_boundaries_button = new QPushButton(this);
    reset_boundaries_button->setText("Reset boundaries");
    g_layout->addRow(reset_boundaries_button);
    connect(reset_boundaries_button, &QPushButton::clicked, presenter, &ChartPresenter::resetBoundaries);

    auto clear_series_button = new QPushButton();
    clear_series_button->setText("Clear all series");
    g_layout->addRow(clear_series_button);
    connect(clear_series_button, &QPushButton::clicked, presenter, &ChartPresenter::clear_data);

    auto save_file_button = new QPushButton();
    save_file_button->setText("Save file");
    g_layout->addRow(save_file_button);
    connect(save_file_button, &QPushButton::clicked, [this, presenter]() {
      auto file_name = QFileDialog::getSaveFileName(this, tr("Create new rtt file"), "", tr("(*.rtt)"));

      QFile file(file_name);
      if (file.open(QIODevice::ReadWrite)) {

          QTextStream stream(&file);
          stream << QString::fromStdString(presenter->to_json().dump()) << endl;
          file.resize(file.pos());

      }
    });

    auto load_from_file_button = new QPushButton();
    load_from_file_button->setText("Load file");
    g_layout->addRow(load_from_file_button);
    connect(load_from_file_button, &QPushButton::clicked, [this, presenter]() {
      auto file_name = QFileDialog::getOpenFileName(this, tr("Open rtt file"), "", tr("(*.rtt)"));
      QFile file(file_name);
      if (file.open(QIODevice::ReadOnly)) {
          QString data_from_file;
          QTextStream in(&file);
          while (!in.atEnd()) {
              QString line = in.readLine();
              data_from_file.append(line);
          }
          json chart_json = json::parse(data_from_file.toStdString());

      }
    });

    series_overview_layout->addWidget(group);


    series_overview_widget->setLayout(series_overview_scroll_layout);
    dialog_splitter->addWidget(series_overview_widget);
    series_overview_widget->setMaximumWidth(380);

    // chart
    auto chart = new QChartView();
    chart->chart()->setMinimumHeight(300);
    dialog_splitter->addWidget(chart);
    chart->chart()->setBackgroundBrush(QColor(33, 33, 33));
    chart->setRenderHint(QPainter::Antialiasing);
    chart->chart()->createDefaultAxes();

    if (presenter->is_dark_theme()) {
        chart->chart()->setTheme(QChart::ChartThemeDark);
        chart->chart()->setBackgroundBrush(QColor(33, 33, 33));
    } else {
        chart->chart()->setTheme(QChart::ChartThemeLight);
        chart->chart()->setBackgroundBrush(QColor(255, 255, 255));
    }

    chart->chart()->addAxis(presenter->getxAxis(), Qt::AlignBottom);
    chart->chart()->addAxis(presenter->getyAxis(), Qt::AlignLeft);

    presenter->getxAxis()->setTitleText("Time");
    presenter->getyAxis()->setTitleText("Rate");

    presenter->getxAxis()->setRange(0, 10);
    presenter->getyAxis()->setRange(0, 10);

    presenter->getxAxis()->setTickCount(10);
    presenter->getyAxis()->setTickCount(10);

//    presenter->setxAxis(dynamic_cast<QValueAxis *>(chart->chart()->axes(Qt::Horizontal)[0]));
//    presenter->setyAxis(dynamic_cast<QValueAxis *>(chart->chart()->axes(Qt::Vertical)[0]));
    chart->chart()->addAxis(presenter->getxAxis(), Qt::AlignBottom);
    chart->chart()->addAxis(presenter->getyAxis(), Qt::AlignLeft);

    auto timer = new QTimer(this);
    connect(timer, &QTimer::timeout, presenter, &ChartPresenter::apply_data);
    timer->start(Helpers::frequency_hz_to_millis(presenter->get_update_frequency()));

    connect(presenter, &ChartPresenter::update_frequency_changed, [timer](int frequency) {
      timer->stop();
      timer->start(Helpers::frequency_hz_to_millis(frequency));
    });

    //////// VIEW --> MODEL CONNECTIONS //////////
    connect(add_series_button, &QPushButton::clicked, presenter, &ChartPresenter::add_new_series);
    connect(theme_checkbox, &QCheckBox::toggled, presenter, &ChartPresenter::set_theme);

    //////// MODEL --> VIEW CONNECTIONS //////////
    connect(presenter,
            &ChartPresenter::seriesAdded,
            [this, series_overview_layout, chart, presenter](SeriesPresenter *series_presenter) {
              auto seriesView = new SeriesView(series_presenter);
              seriesMap.insert(std::make_pair(series_presenter, seriesView));
              series_overview_layout->addWidget(seriesView);
              chart->chart()->addSeries(series_presenter->get_qt_series());

              series_presenter->get_qt_series()->attachAxis(series_presenter->getParent()->getxAxis());
              series_presenter->get_qt_series()->attachAxis(series_presenter->getParent()->getyAxis());
            });

    connect(presenter,
            &ChartPresenter::seriesRemoved,
            [this, series_overview_layout, chart](SeriesPresenter *series_presenter) {
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




    for (auto series_presenter : presenter->get_series_list()) {
        auto seriesView = new SeriesView(series_presenter);
        seriesMap.insert(std::make_pair(series_presenter, seriesView));
        series_overview_layout->addWidget(seriesView);
        chart->chart()->addSeries(series_presenter->get_qt_series());

        series_presenter->get_qt_series()->attachAxis(series_presenter->getParent()->getxAxis());
        series_presenter->get_qt_series()->attachAxis(series_presenter->getParent()->getyAxis());
    }

}
