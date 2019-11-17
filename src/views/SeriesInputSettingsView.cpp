//
// Created by Lukas Bos on 15/11/2019.
//

#include <QVBoxLayout>
#include <QComboBox>
#include <roboteam_proto/Channels.h>
#include <QLabel>
#include <src/presenters/SeriesSettingsPresenter.h>
#include <src/views/components/ConfirmationWidget.h>
#include <QPushButton>
#include <src/utils/Helpers.h>
#include "SeriesInputSettingsView.h"
#include "FilterView.h"

SeriesInputSettingsView::SeriesInputSettingsView(SeriesSettingsPresenter * presenter, QWidget * parent) : QWidget(parent) {
    auto topLayout = new QVBoxLayout();

    auto network_settings_layout = new QVBoxLayout();
    network_settings_layout->setAlignment(Qt::AlignTop);
    topLayout->addLayout(network_settings_layout);
    setLayout(topLayout);

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
    for (auto filter_presenter : presenter->get_filters()) {
        auto filterView = new FilterView(filter_presenter, this);
        filterMap.insert(std::make_pair(filter_presenter, filterView));
        current_filters_layout->addWidget(filterView);
    }
    network_settings_layout->addLayout(current_filters_layout);

    auto add_new_filter_button = new QPushButton();
    add_new_filter_button->setText("Add new filter");

    network_settings_layout->addWidget(add_new_filter_button);


    ////// VIEW --> MODEL CONNECTIONS /////
    connect(add_new_filter_button, &QPushButton::clicked, presenter, &SeriesSettingsPresenter::add_new_filter);
//    connect(channel_combo_box, &QComboBox::currentTextChanged, [this](const QString &text) {
//     // selected_topic_name = text;
//     // select_field_dialog->update_filters_layout(text);
//    });




    ////// MODEL --> VIEW CONNECTIONS /////
    connect(presenter, &SeriesSettingsPresenter::filterAdded, [this, presenter, current_filters_layout](FilterPresenter * new_filter) {
      auto filterView = new FilterView(new_filter, this);
      auto pair = std::make_pair(new_filter, filterView);
      filterMap.insert(pair);
      current_filters_layout->addWidget(filterView);
    });

    connect(presenter, &SeriesSettingsPresenter::filterRemoved, [this, presenter, current_filters_layout](FilterPresenter * removed_filter) {
      auto filterView = filterMap.at(removed_filter);
      filterView->hide();
      current_filters_layout->removeWidget(filterView);
      filterMap.erase(removed_filter);
    });




    presenter->createSnapShot();
    connect(presenter, &SeriesSettingsPresenter::modelChanged, [this, presenter, current_filters_layout]() {
        for (auto const& [model, view] : filterMap) {
            view->hide();
            current_filters_layout->removeWidget(view);
        }

        filterMap.clear();

          for (auto filter_presenter : presenter->get_filters()) {
              auto filterView = new FilterView(filter_presenter, this);
              filterMap.insert(std::make_pair(filter_presenter, filterView));
              current_filters_layout->addWidget(filterView);
          }

        presenter->createSnapShot();
    });



    auto confirmWidget = new ConfirmationWidget("Cancel", "Apply", this);
    topLayout->addWidget(confirmWidget);
    connect(confirmWidget, &ConfirmationWidget::cancel, presenter, &SeriesSettingsPresenter::rollBack);
    connect(confirmWidget, &ConfirmationWidget::confirm, presenter, &SeriesSettingsPresenter::confirm);
}

