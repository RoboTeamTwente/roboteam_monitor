#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <include/ChartSeriesDialog.h>
#include "views/SeriesView.h"
#include "models/SeriesModel.h"
#include <QtCharts/QtCharts>

SeriesView::SeriesView(SeriesModel * seriesModel) : QGroupBox("", nullptr), seriesModel(seriesModel) {
    seriesModel->set_view(this);

    this->setCheckable(false);
    setMaximumHeight(260);
    auto series_layout = new QVBoxLayout();
    this->setLayout(series_layout);

    auto title_and_color_layout = new QHBoxLayout();
    auto series_title_line_edit = new QLineEdit();
    series_title_line_edit->setText(seriesModel->get_qt_series()->name());
    title_and_color_layout->addWidget(series_title_line_edit);
    auto change_color_button = new QPushButton();
    change_color_button->setText("");
    title_and_color_layout->addWidget(change_color_button);

    auto color_dialog = new QColorDialog();


    auto visible_checkbox = new QCheckBox("visible");
    visible_checkbox->setChecked(true);
    title_and_color_layout->addWidget(visible_checkbox);

    series_layout->addLayout(title_and_color_layout);

    auto delete_series_button = new QPushButton();
    delete_series_button->setText("Remove series");

    delete_series_button->setAutoFillBackground(true);
    delete_series_button->setStyleSheet("background-color: red");

    series_layout->addWidget(delete_series_button);



    auto series_settings_button = new QPushButton();
    series_settings_button->setText("Configuration");
    series_layout->addWidget(series_settings_button);

    auto series_dialog = new ChartSeriesDialog(seriesModel, this);


    //////// VIEW --> MODEL CONNECTIONS //////////

    connect(color_dialog, &QColorDialog::colorSelected, seriesModel, &SeriesModel::set_color);
    connect(color_dialog, &QColorDialog::currentColorChanged, seriesModel, &SeriesModel::set_color);
    connect(visible_checkbox, &QCheckBox::toggled, seriesModel, &SeriesModel::set_visible);

    connect(change_color_button, &QPushButton::clicked, [color_dialog]() {
      color_dialog->exec();
    });

    connect(series_title_line_edit, &QLineEdit::textChanged, seriesModel->get_qt_series(), &QXYSeries::setName);
    connect(series_settings_button, &QPushButton::clicked, [series_dialog]() {
      series_dialog->exec();
    });

    connect(delete_series_button, &QPushButton::clicked, [seriesModel]() {
      // seriesModel->get_parent_model()->delete_series(seriesModel);
    });

    //////// MODEL --> VIEW CONNECTIONS //////////
    connect(seriesModel->get_qt_series(), &QXYSeries::colorChanged, [change_color_button](const QColor & newColor) {
      QString change_color_button_stylesheet = "background-color: " + newColor.name() +";";
      change_color_button->setStyleSheet(change_color_button_stylesheet);
    });

}
