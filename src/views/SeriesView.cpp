#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <src/views/SeriesSettingsDialog.h>
#include "views/SeriesView.h"
#include "src/presenters/SeriesPresenter.h"
#include "src/presenters/SeriesSettingsPresenter.h"

#include <QtCharts/QtCharts>

SeriesView::SeriesView(SeriesPresenter * series_presenter) : QGroupBox("", nullptr), seriesModel(series_presenter) {
    this->setCheckable(false);
    setMaximumHeight(260);
    auto series_layout = new QVBoxLayout();
    this->setLayout(series_layout);

    auto title_and_color_layout = new QHBoxLayout();
    auto series_title_line_edit = new QLineEdit();
    series_title_line_edit->setText(series_presenter->get_qt_series()->name());
    title_and_color_layout->addWidget(series_title_line_edit);
    auto change_color_button = new QPushButton();
    change_color_button->setText("");
    title_and_color_layout->addWidget(change_color_button);

    auto color_dialog = new QColorDialog();
    auto visible_checkbox = new QCheckBox("visible");
    visible_checkbox->setChecked(true);
    title_and_color_layout->addWidget(visible_checkbox);
    series_layout->addLayout(title_and_color_layout);


    auto subscription_label = new QLabel();
    series_layout->addWidget(subscription_label);
    auto filters_label = new QLabel();
    series_layout->addWidget(filters_label);
    auto rate_label = new QLabel();
    series_layout->addWidget(rate_label);
    if (series_presenter->getSettings()) {
        auto type = series_presenter->getSettings()->get_channel_type();
        subscription_label->setText(QString::fromStdString(proto::CHANNELS.at(type).name));
        //TODO add connection

        int filters = series_presenter->getSettings()->get_filters().size();
        filters_label->setText(QString::number(filters, 10) + " filters");
        //TODO add connection


    }

    connect(series_presenter->get_qt_series(), &QXYSeries::QXYSeries::pointsReplaced, [series_presenter, rate_label]() {
      int rate = series_presenter->get_rate();
      int total_packets = series_presenter->get_filtered_packets_rate() + rate;
      rate_label->setText(QString::number(rate, 10) + "/" + QString::number(total_packets, 10) + " packets/s");
    });


    auto buttons_layout = new QHBoxLayout();
    series_layout->addLayout(buttons_layout);

    auto delete_series_button = new QPushButton();
    delete_series_button->setText("Remove");
    delete_series_button->setAutoFillBackground(true);
    delete_series_button->setStyleSheet("background-color: red");
    buttons_layout->addWidget(delete_series_button);

    auto clear_series_button = new QPushButton();
    clear_series_button->setText("Clear");
    buttons_layout->addWidget(clear_series_button);

    auto series_settings_button = new QPushButton();
    series_settings_button->setText("Configuration");
    buttons_layout->addWidget(series_settings_button);


    //////// VIEW --> MODEL CONNECTIONS //////////
    connect(color_dialog, &QColorDialog::colorSelected, series_presenter, &SeriesPresenter::set_color);
    connect(color_dialog, &QColorDialog::currentColorChanged, series_presenter, &SeriesPresenter::set_color);
    connect(visible_checkbox, &QCheckBox::toggled, series_presenter, &SeriesPresenter::set_visible);
    connect(change_color_button, &QPushButton::clicked, [color_dialog]() {
      color_dialog->exec();
    });
    connect(series_title_line_edit, &QLineEdit::textChanged, series_presenter->get_qt_series(), &QXYSeries::setName);
    connect(series_settings_button, &QPushButton::clicked, [this, series_presenter]() {
      auto copy = series_presenter->get_settings_copy();
      auto series_dialog = new SeriesSettingsDialog(copy, this);
        connect(series_dialog, &QDialog::accepted, [series_presenter, copy]() {
            series_presenter->applySettings(copy);
        });

      connect(series_dialog, &QDialog::rejected, [series_presenter]() {

      });
      series_dialog->exec();
    });
    connect(delete_series_button, &QPushButton::clicked, [series_presenter]() {
       series_presenter->getParent()->delete_series(series_presenter);
    });
    connect(clear_series_button, &QPushButton::clicked, series_presenter, &SeriesPresenter::clear_data);


      //////// MODEL --> VIEW CONNECTIONS //////////
    connect(series_presenter->get_qt_series(), &QXYSeries::colorChanged, [change_color_button](const QColor & newColor) {
      QString change_color_button_stylesheet = "background-color: " + newColor.name() +";";
      change_color_button->setStyleSheet(change_color_button_stylesheet);
    });
}
