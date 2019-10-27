#include <include/ChartSeries.h>
#include <roboteam_utils/constants.h>
#include <include/Helpers.h>
#include "ChartSeriesDialog.h"

ChartSeriesDialog::ChartSeriesDialog(ChartSeries * series) : QDialog(series) {
  auto dialog_layout = new QVBoxLayout(this);
  setLayout(dialog_layout);
  auto tab_widget = new QTabWidget();
  dialog_layout->addWidget(tab_widget);

  QWidget * network_settings_tab = create_network_settings_tab(series);
  tab_widget->addTab(network_settings_tab, "Data");
}

QWidget * ChartSeriesDialog::create_network_settings_tab(ChartSeries * series) {
  auto network_settings_tab = new QWidget();
  auto network_settings_layout = new QVBoxLayout();
  network_settings_tab->setLayout(network_settings_layout);

  // communication layout
  auto comm_layout = new QHBoxLayout();
  auto channel_combo_box = new QComboBox();
  comm_layout->addWidget(channel_combo_box);
  for (auto const &channel : roboteam_utils::CHANNELS) {
      channel_combo_box->addItem(QString::fromStdString(channel.second.name));
  }
  network_settings_layout->addLayout(comm_layout);
  connect(channel_combo_box, &QComboBox::currentTextChanged, this, &ChartSeriesDialog::update_filters_layout);

  // Filters layout
  filters_layout = new QFormLayout();
  network_settings_layout->addLayout(filters_layout);

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

  connect(apply_network_settings_button, &QPushButton::clicked, [this, series, channel_combo_box]() {
    for (auto const &channel : roboteam_utils::CHANNELS) {
        if (channel_combo_box->currentText() == QString::fromStdString(channel.second.name)) {
            series->update_channel(channel.first);
            this->close();
        }
    }
  });

  return network_settings_tab;
}

void ChartSeriesDialog::update_filters_layout(const QString & topic_name) {
    clearLayout(filters_layout);
    auto descriptor = Helpers::get_descriptor_for_topic(topic_name);
    for (int i = 0; i < descriptor->field_count(); ++i) {
        auto field_descriptor = descriptor->field(i);
        auto text_filter = new QLineEdit();

        filters_layout->addRow(QString::fromStdString(field_descriptor->name()), text_filter);

        auto type = field_descriptor->message_type();
        if (type) {
            for (int j = 0; j < type->field_count(); ++j) {
                auto text_filter_2 = new QLineEdit();
                filters_layout->addRow(QString::fromStdString(type->field(j)->name()), text_filter_2);
            }
        }
    }
}

/// delete a layout and its children
void ChartSeriesDialog::clearLayout(QLayout* layout) {
    QLayoutItem* item;
    while ((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}
