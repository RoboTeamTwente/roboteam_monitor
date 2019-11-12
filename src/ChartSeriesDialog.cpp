#include <include/ChartSeries.h>
#include <roboteam_utils/constants.h>
#include <include/Helpers.h>
#include <include/AddFilterDialog.h>
#include "ChartSeriesDialog.h"

ChartSeriesDialog::ChartSeriesDialog(ChartSeries * series) : QDialog(series) {
  setMinimumWidth(600);
  auto dialog_layout = new QVBoxLayout(this);
  setLayout(dialog_layout);
  auto tab_widget = new QTabWidget();
  dialog_layout->addWidget(tab_widget);
  QWidget * network_settings_tab = create_network_settings_tab(series);
  tab_widget->addTab(network_settings_tab, "Data");
}

QWidget * ChartSeriesDialog::create_network_settings_tab(ChartSeries * series) {
  auto network_settings_tab = new QWidget();
  network_settings_layout = new QVBoxLayout();
  network_settings_tab->setLayout(network_settings_layout);

  // communication layout
  auto comm_layout = new QHBoxLayout();
  channel_combo_box = new QComboBox();
  comm_layout->addWidget(channel_combo_box);
  for (auto const &channel : proto::CHANNELS) {
      channel_combo_box->addItem(QString::fromStdString(channel.second.name));
  }
    connect(channel_combo_box, &QComboBox::currentTextChanged, [this](QString text) {
        selected_topic_name = text;
    });

    network_settings_layout->addLayout(comm_layout);


  auto current_filters_label = new QLabel();
  current_filters_label->setText("Active filters");
  network_settings_layout->addWidget(current_filters_label);

  auto current_filters_layout = new QVBoxLayout();
  for (auto filter : series->get_filters()) {
      create_filter_view(current_filters_layout, filter);
  }


    network_settings_layout->addLayout(current_filters_layout);

    auto add_new_filter_button = new QPushButton();
    add_new_filter_button->setText("Add new filter");
    connect(add_new_filter_button, &QPushButton::clicked, [this, series, current_filters_layout]() {
        auto new_filter = series->add_new_filter();
        create_filter_view(current_filters_layout, *new_filter);
    });
    network_settings_layout->addWidget(add_new_filter_button);


  auto buttons_layout = new QHBoxLayout();
  network_settings_layout->addLayout(buttons_layout);

  // Cancel button
  auto cancel_button = new QPushButton();
  cancel_button->setText("Cancel");
  buttons_layout->addWidget(cancel_button);
  connect(cancel_button, &QPushButton::clicked, [this]() {
    this->close();
  });

  // Apply button
  auto apply_network_settings_button = new QPushButton();
  apply_network_settings_button->setText("Apply");
  apply_network_settings_button->setStyleSheet("background-color: green;");
  buttons_layout->addWidget(apply_network_settings_button);

  connect(apply_network_settings_button, &QPushButton::clicked, [this, series]() {
    for (auto const &channel : proto::CHANNELS) {
        if (channel_combo_box->currentText() == QString::fromStdString(channel.second.name)) {
            series->update_channel(channel.first);
            this->close();
        }
    }
  });
  return network_settings_tab;
}

void ChartSeriesDialog::create_filter_view(QVBoxLayout *current_filters_layout, const Filter &filter) const {
    auto filter_layout = new QHBoxLayout();
    auto add_filter_dialog = new AddFilterDialog((QWidget *) this);
    auto add_filter_button = new QPushButton();
    if (filter.field_descriptor) {
        add_filter_button->setText(QString::fromStdString(filter.field_descriptor->name()));
    } else {
        add_filter_button->setText("Select...");
    }
    connect(add_filter_button, &QPushButton::clicked, add_filter_dialog, &QDialog::open);
    connect(add_filter_dialog, &AddFilterDialog::finished, [=]() {
      add_filter_button->setText(QString::fromStdString(add_filter_dialog->get_selected_field_descriptor()->name()));
    });
    connect(channel_combo_box, &QComboBox::currentTextChanged, add_filter_dialog, &AddFilterDialog::update_filters_layout);
    if (selected_topic_name != "") {
        add_filter_dialog->update_filters_layout(selected_topic_name);
    }
    filter_layout->addWidget(add_filter_button);
    auto filter_value_edit = new QLineEdit();
    filter_layout->addWidget(filter_value_edit);
    current_filters_layout->addLayout(filter_layout);
}


