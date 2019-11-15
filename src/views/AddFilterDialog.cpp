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
    connect(filters_tree_widget, &SelectTypeWidget::fieldSelected, this, &AddFilterDialog::set_selected_field_descriptor);

    // for a double click we select and close immediately
    connect(filters_tree_widget, &SelectTypeWidget::fieldSelectedAndClose, [this](const google::protobuf::FieldDescriptor * field_descriptor) {
      set_selected_field_descriptor(field_descriptor);
      emit valueChanged(field_descriptor);
      close();
    });

    connect(select_button, &QPushButton::clicked, [this]() {
      if(selectedFieldDescriptor) {
          emit valueChanged(selectedFieldDescriptor);
      }
      this->close();
    });

    auto topic = proto::CHANNELS.at(proto::ChannelType::GEOMETRY_CHANNEL).name;
    filters_tree_widget->update_filters_layout(QString::fromStdString(topic));




}

void AddFilterDialog::set_selected_field_descriptor(const google::protobuf::FieldDescriptor * selected_field_descriptor) {
    selectedFieldDescriptor = selected_field_descriptor;
}

void AddFilterDialog::update_filters_layout(const QString & topic_name) {
    filters_tree_widget->update_filters_layout(topic_name);
}
