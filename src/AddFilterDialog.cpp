//
// Created by Lukas Bos on 11/11/2019.
//

#include <QVBoxLayout>
#include <QScrollArea>
#include <roboteam_proto/Channels.h>
#include "AddFilterDialog.h"

AddFilterDialog::AddFilterDialog(QWidget * parent) : QDialog(parent) {
    auto add_filter_layout = new QVBoxLayout();
    setLayout(add_filter_layout);

    auto filter_select_dialog = new QDialog();
    auto tree_layout = new QVBoxLayout();
    filter_select_dialog->setLayout(tree_layout);
    filters_tree_widget = new SelectTypeWidget(this);

    connect(filters_tree_widget, &SelectTypeWidget::fieldSelected, this, &AddFilterDialog::set_selected_field_descriptor);

    tree_layout->addWidget(filters_tree_widget);

    auto scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    auto inner = new QFrame(scroll);
    inner->setLayout(tree_layout);
    scroll->setWidget(inner);
    add_filter_layout->addWidget(scroll);

    auto topic = proto::CHANNELS.at(proto::ChannelType::GEOMETRY_CHANNEL).name;
    filters_tree_widget->update_filters_layout(QString::fromStdString(topic));
}

const google::protobuf::FieldDescriptor *AddFilterDialog::get_selected_field_descriptor() const {
    return selectedFieldDescriptor;
}

void AddFilterDialog::set_selected_field_descriptor(const google::protobuf::FieldDescriptor * selected_field_descriptor) {
    selectedFieldDescriptor = selected_field_descriptor;
}

void AddFilterDialog::update_filters_layout(const QString & topic_name) {
filters_tree_widget->update_filters_layout(topic_name);
}

