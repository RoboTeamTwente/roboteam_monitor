#include <include/ChartSeries.h>
#include <roboteam_utils/constants.h>
#include <include/Helpers.h>
#include <include/AddFilterDialog.h>
#include "ChartSeriesDialog.h"

ChartSeriesDialog::ChartSeriesDialog(ChartSeries *series) : QDialog(series) {
    setMinimumWidth(600);
    auto dialog_layout = new QVBoxLayout(this);
    setLayout(dialog_layout);
    auto tab_widget = new QTabWidget();
    dialog_layout->addWidget(tab_widget);
    QWidget *network_settings_tab = create_network_settings_tab(series);
    tab_widget->addTab(network_settings_tab, "Input");

    QWidget * visualization_tab = create_visualization_settings_tab(series);
    tab_widget->addTab(visualization_tab, "Visualization");


    auto buttons_layout = new QHBoxLayout();
    dialog_layout->addLayout(buttons_layout);

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
          if (channel_combo_box->currentText()==QString::fromStdString(channel.second.name)) {
              series->update_channel(channel.first);
              this->close();
          }
      }
    });

}

QWidget *ChartSeriesDialog::create_network_settings_tab(ChartSeries *series) {
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
    connect(channel_combo_box, &QComboBox::currentTextChanged, [this](const QString &text) {
      selected_topic_name = text;
    });

    network_settings_layout->addLayout(comm_layout);

    network_settings_layout->setAlignment(Qt::AlignTop);

    auto current_filters_label = new QLabel();
    current_filters_label->setText("Active filters");
    network_settings_layout->addWidget(current_filters_label);

    auto current_filters_layout = new QVBoxLayout();
    for (auto filter : series->get_filters()) {
        auto filter_widget = create_filter_widget(current_filters_layout, filter, series);
        current_filters_layout->addWidget(filter_widget);
    }
    network_settings_layout->addLayout(current_filters_layout);

    auto add_new_filter_button = new QPushButton();
    add_new_filter_button->setText("Add new filter");
    connect(add_new_filter_button, &QPushButton::clicked, [this, series, current_filters_layout]() {
      auto new_filter = series->add_new_filter();
      auto filter_widget = create_filter_widget(current_filters_layout, new_filter, series);
      current_filters_layout->addWidget(filter_widget);
    });
    network_settings_layout->addWidget(add_new_filter_button);


    return network_settings_tab;
}

QWidget *ChartSeriesDialog::create_filter_widget(QLayout *parent, Filter * filter, ChartSeries * series) const {
    auto filter_widget = new QWidget();
    auto filter_layout = new QHBoxLayout();
    filter_widget->setLayout(filter_layout);
    auto add_filter_dialog = new AddFilterDialog((QWidget *) this);
    auto add_filter_button = new QPushButton();
    if (filter->field_descriptor) {
        add_filter_button->setText(QString::fromStdString(filter->field_descriptor->name()));
    } else {
        add_filter_button->setText("Select...");
    }
    connect(add_filter_button, &QPushButton::clicked, add_filter_dialog, &QDialog::open);
    connect(add_filter_dialog, &AddFilterDialog::valueChanged, [add_filter_button, filter](const google::protobuf::FieldDescriptor * field_descriptor) {
      add_filter_button->setText(QString::fromStdString(field_descriptor->name()));
      filter->field_descriptor = const_cast<google::protobuf::FieldDescriptor *>(field_descriptor);
    });

    if (selected_topic_name!="") {
        add_filter_dialog->update_filters_layout(selected_topic_name);
    }
    filter_layout->addWidget(add_filter_button);

    auto filter_value_edit = new QLineEdit();
    filter_layout->addWidget(filter_value_edit);

    auto rm_filter_button = new QPushButton();
    rm_filter_button->setText("Remove");
    rm_filter_button->setStyleSheet("background-color: red;");
    filter_layout->addWidget(rm_filter_button);

    connect(rm_filter_button, &QPushButton::clicked, [parent, filter_widget, series, filter]() {
        filter_widget->hide();
        parent->removeWidget(filter_widget);
        series->removeFilter(filter);
        std::cerr << "WARNING NOT REALLY REMOVING FILTER" << std::endl;
    });

    return filter_widget;
}

QWidget *ChartSeriesDialog::create_visualization_settings_tab(ChartSeries *series) {
    auto visualization_widget = new QWidget();
    auto visualization_layout = new QHBoxLayout();
    visualization_widget->setLayout(visualization_layout);

    QGroupBox *groupBox = new QGroupBox(tr("Data to plot"));
    QRadioButton *radio_rate = new QRadioButton("Data rate (packets/s)");
    QRadioButton *radio_field = new QRadioButton("Custom field");
    radio_rate->setChecked(true);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(radio_rate);
    vbox->addWidget(radio_field);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    visualization_layout->addWidget(groupBox);

    return visualization_widget;
}


