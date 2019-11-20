//
// Created by Lukas Bos on 11/11/2019.
//

#include <QVBoxLayout>
#include <QScrollArea>
#include <roboteam_proto/Channels.h>
#include "AddFilterDialog.h"
#include <QPushButton>

AddFilterDialog::AddFilterDialog(QWidget * parent) : QDialog(parent) {
    auto add_filter_layout = new QVBoxLayout();
    setLayout(add_filter_layout);

    auto filter_select_dialog = new QDialog();
    auto tree_layout = new QVBoxLayout();
    filter_select_dialog->setLayout(tree_layout);
    filters_tree_widget = new SelectTypeWidget(this);



    tree_layout->addWidget(filters_tree_widget);

    auto scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    auto inner = new QFrame(scroll);
    inner->setLayout(tree_layout);
    scroll->setWidget(inner);
    add_filter_layout->addWidget(scroll);

    auto buttons_layout = new QHBoxLayout();
    add_filter_layout->addLayout(buttons_layout);
    // Cancel button
    auto cancel_button = new QPushButton();
    cancel_button->setText("Cancel");
    buttons_layout->addWidget(cancel_button);


    // Apply button
    auto select_button = new QPushButton();
    select_button->setText("Select");
    select_button->setStyleSheet("background-color: green;");
    buttons_layout->addWidget(select_button);




    connect(cancel_button, &QPushButton::clicked, [this]() {
      this->close();
    });

    // for a selection we can still use the select or cancel button
    connect(filters_tree_widget, &SelectTypeWidget::fieldSelected, this, &AddFilterDialog::set_selected_field_definition);

    // for a double click we select and close immediately
    connect(filters_tree_widget, &SelectTypeWidget::fieldSelectedAndClose, [this](FieldDefinition * field_definition) {
      set_selected_field_definition(field_definition);
      emit valueChanged(field_definition);
      close();
    });

    connect(select_button, &QPushButton::clicked, [this]() {
      if(selected_field_definition) {
          emit valueChanged(selected_field_definition);
      }
      this->close();
    });

    auto topic = proto::CHANNELS.at(proto::ChannelType::GEOMETRY_CHANNEL).name;
    filters_tree_widget->update_filters_layout(QString::fromStdString(topic));
}

void AddFilterDialog::set_selected_field_definition(FieldDefinition * field_definition) {
    selected_field_definition = field_definition;
}

void AddFilterDialog::update_filters_layout(const QString & topic_name) {
    filters_tree_widget->update_filters_layout(topic_name);
}
