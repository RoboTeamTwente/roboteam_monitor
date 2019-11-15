//
// Created by Lukas Bos on 15/11/2019.
//

#include <QVBoxLayout>
#include <QComboBox>
#include <roboteam_proto/Channels.h>
#include <QLabel>
#include <src/models/SeriesInputSettingsModel.h>
#include <src/views/components/ConfirmationWidget.h>
#include <QPushButton>
#include "SeriesInputSettingsView.h"
#include "FilterView.h"

SeriesInputSettingsView::SeriesInputSettingsView(SeriesInputSettingsModel * model, QWidget * parent) : QWidget(parent) {
    auto network_settings_layout = new QVBoxLayout();
    network_settings_layout->setAlignment(Qt::AlignTop);
    setLayout(network_settings_layout);

    // communication layout
    auto comm_layout = new QHBoxLayout();
    auto channel_combo_box = new QComboBox();
    comm_layout->addWidget(channel_combo_box);
    for (auto const &channel : proto::CHANNELS) {
        channel_combo_box->addItem(QString::fromStdString(channel.second.name));
    }
    network_settings_layout->addLayout(comm_layout);

    auto current_filters_label = new QLabel();
    current_filters_label->setText("Active filters");
    network_settings_layout->addWidget(current_filters_label);

    auto current_filters_layout = new QVBoxLayout();
    for (auto filter : model->get_filters()) {
        auto filterView = new FilterView(filter, model, this);
        filterMap.insert(std::make_pair(filter, filterView));
        current_filters_layout->addWidget(filterView);
    }
    network_settings_layout->addLayout(current_filters_layout);

    auto add_new_filter_button = new QPushButton();
    add_new_filter_button->setText("Add new filter");

    network_settings_layout->addWidget(add_new_filter_button);


    auto confirmWidget = new ConfirmationWidget("Cancel", "Apply", this);
    network_settings_layout->addWidget(confirmWidget);


    ////// VIEW --> MODEL CONNECTIONS /////
    connect(add_new_filter_button, &QPushButton::clicked, model, &SeriesInputSettingsModel::add_new_filter);
//    connect(channel_combo_box, &QComboBox::currentTextChanged, [this](const QString &text) {
//     // selected_topic_name = text;
//     // select_field_dialog->update_filters_layout(text);
//    });

    ////// MODEL --> VIEW CONNECTIONS /////
    connect(model, &SeriesInputSettingsModel::filterAdded, [this, model, current_filters_layout](FilterModel * new_filter) {
      auto filterView = new FilterView(new_filter, model, this);
      auto pair = std::make_pair(new_filter, filterView);
      filterMap.insert(pair);
      current_filters_layout->addWidget(filterView);
    });

    connect(model, &SeriesInputSettingsModel::filterRemoved, [this, model, current_filters_layout](FilterModel * new_filter) {
      auto filterView = filterMap.at(new_filter);
      filterView->hide();
      current_filters_layout->removeWidget(filterView);
    });
}
