//
// Created by Lukas Bos on 11/11/2019.
//

#include <include/Constants.h>
#include <include/Helpers.h>
#include "SelectTypeWidget.h"
#include <QLineEdit>
#include <QPushButton>
#include <QDialog>

SelectTypeWidget::SelectTypeWidget(QDialog * parent) : QTreeWidget(static_cast<QWidget *>(parent)), parent_widget(parent) {
    top_level_tree_item = new QTreeWidgetItem();
    addTopLevelItem(top_level_tree_item);
    top_level_tree_item->setText(0, "Filters");

    setMinimumWidth(FILTER_TREE_VIEW_WIDTH);
    setColumnCount(2);
    setColumnWidth(0, 150);
    setColumnWidth(1, 200);

    auto header = headerItem();
    header->setText(0, "Item");
    header->setText(1, "Type");
    header->setText(2, "Value");
}

void SelectTypeWidget::update_filters_layout(const QString & topic_name) {
    top_level_tree_item->takeChildren();

    top_level_tree_item->setExpanded(true);
    auto descriptor = Helpers::get_descriptor_for_topic(topic_name);
    if (descriptor) {
        add_filter_descriptor(descriptor, 0, top_level_tree_item);
    }
}


void SelectTypeWidget::add_filter_descriptor(const google::protobuf::Descriptor * descriptor, int depth, QTreeWidgetItem * parent) {
    for (int i = 0; i < descriptor->field_count(); ++i) {
        auto field_descriptor = descriptor->field(i);
        auto row_widget = new QTreeWidgetItem();
        parent->addChild(row_widget);

        // set the name in the first column
        row_widget->setText(0, QString::fromStdString(field_descriptor->name()));

        // put the type in the second column
        row_widget->setText(1, Helpers::get_actual_typename(field_descriptor));

        // put a lineEdit in the third column
        auto select_button = new QPushButton();
        select_button->setText("Select");
        connect(select_button, &QPushButton::clicked, [=]() {
            emit fieldSelected(field_descriptor);
            parent_widget->close();
        });
        setItemWidget(row_widget, 2, select_button);

        // do some nice recursion for the children of this item
        auto child_descriptor = field_descriptor->message_type();
        if (child_descriptor) {
            add_filter_descriptor(child_descriptor, ++depth, row_widget);
        }
    }
}

#include "include/moc_SelectTypeWidget.cpp"