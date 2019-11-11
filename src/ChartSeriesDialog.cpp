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
  network_settings_layout = new QVBoxLayout();
  network_settings_tab->setLayout(network_settings_layout);

  // communication layout
  auto comm_layout = new QHBoxLayout();
  auto channel_combo_box = new QComboBox();
  comm_layout->addWidget(channel_combo_box);
  for (auto const &channel : proto::CHANNELS) {
      channel_combo_box->addItem(QString::fromStdString(channel.second.name));
  }
  network_settings_layout->addLayout(comm_layout);
  connect(channel_combo_box, &QComboBox::currentTextChanged, this, &ChartSeriesDialog::update_filters_layout);

  // Filters layout

    auto tree_layout = new QVBoxLayout();
    filters_tree_widget = new QTreeWidget();
    top_level_tree_item = new QTreeWidgetItem();

    filters_tree_widget->addTopLevelItem(top_level_tree_item);
    top_level_tree_item->setText(0, "Filters");

    tree_layout->addWidget(filters_tree_widget);
    auto scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    auto inner = new QFrame(scroll);
    inner->setLayout(tree_layout);
    scroll->setWidget(inner);
    network_settings_layout->addWidget(scroll);

    auto topic = proto::CHANNELS.at(proto::ChannelType::GEOMETRY_CHANNEL).name;
    update_filters_layout(QString::fromStdString(topic));

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
    for (auto const &channel : proto::CHANNELS) {
        if (channel_combo_box->currentText() == QString::fromStdString(channel.second.name)) {
            series->update_channel(channel.first);
            this->close();
        }
    }
  });

  return network_settings_tab;
}

void ChartSeriesDialog::update_filters_layout(const QString & topic_name) {
    top_level_tree_item->takeChildren();

    filters_tree_widget->setMinimumWidth(400);
    filters_tree_widget->setColumnCount(2);
    filters_tree_widget->setColumnWidth(0, 150);
    filters_tree_widget->setColumnWidth(1, 200);

    QTreeWidgetItem* header = filters_tree_widget->headerItem();
    header->setText(0, "item");
    header->setText(1, "type");
    header->setText(2, "value");

    top_level_tree_item->setExpanded(true);
    auto descriptor = Helpers::get_descriptor_for_topic(topic_name);
    add_filter_descriptor(descriptor, 0, top_level_tree_item);
}

void ChartSeriesDialog::add_filter_descriptor(const google::protobuf::Descriptor * descriptor, int depth, QTreeWidgetItem * parent) {
    for (int i = 0; i < descriptor->field_count(); ++i) {
        auto field_descriptor = descriptor->field(i);
        auto row_widget = new QTreeWidgetItem();
        parent->addChild(row_widget);

        // set the name in the first column
        row_widget->setText(0, QString::fromStdString(field_descriptor->name()));

        // put the type in the second column
        row_widget->setText(1, Helpers::get_actual_typename(field_descriptor));

        // put a lineEdit in the third column
        auto text_edit = new QLineEdit();
        filters_tree_widget->setItemWidget(row_widget, 2 , text_edit);

        // do some nice recursion for the children of this item
        auto child_descriptor = field_descriptor->message_type();
        if (child_descriptor) {
            add_filter_descriptor(child_descriptor, ++depth, row_widget);
        }
    }
}


