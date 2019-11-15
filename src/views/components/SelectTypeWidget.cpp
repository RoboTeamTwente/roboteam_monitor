//
// Created by Lukas Bos on 11/11/2019.
//

#include <src/utils/Constants.h>
#include <src/utils/Helpers.h>
#include "SelectTypeWidget.h"
#include <QLineEdit>
#include <QPushButton>
#include <QDialog>

SelectTypeWidget::SelectTypeWidget(AddFilterDialog * parent) : QTreeWidget((QWidget *)parent), parent_widget(parent) {
    top_level_tree_item = new QTreeWidgetItem();
    addTopLevelItem(top_level_tree_item);
    top_level_tree_item->setText(0, "Filters");

    setMinimumWidth(FILTER_TREE_VIEW_WIDTH);
    setColumnCount(2);
    setColumnWidth(0, 150);
    setColumnWidth(1, 100);

    auto header = headerItem();
    header->setText(0, "Item");
    header->setText(1, "Type");
}

void SelectTypeWidget::update_filters_layout(const QString & topic_name) {
    top_level_tree_item->takeChildren();

    top_level_tree_item->setExpanded(true);
    auto descriptor = Helpers::get_descriptor_for_topic(topic_name);
    if (descriptor) {
        add_filter_descriptor(descriptor, {}, top_level_tree_item);
    }
}


void SelectTypeWidget::add_filter_descriptor(const google::protobuf::Descriptor * descriptor, const std::vector<int> & field_numbers, QTreeWidgetItem * parent) {
    for (int i = 0; i < descriptor->field_count(); ++i) {

        std::vector<int> fieldNumbersToHere = field_numbers;
        fieldNumbersToHere.push_back(i);

        auto field_descriptor = descriptor->field(i);
        auto row_widget = new QTreeWidgetItem();
        parent->addChild(row_widget);

        // set the name in the first column and type in the second column
        row_widget->setText(0, QString::fromStdString(field_descriptor->name()));
        row_widget->setText(1, Helpers::get_actual_typename(field_descriptor));

        // Select the item and close the dialog on double click
        connect(this, &QTreeWidget::itemActivated, [this, row_widget, field_descriptor, fieldNumbersToHere](QTreeWidgetItem *item, int column) {
            if (item == row_widget) {
                emit fieldSelectedAndClose(field_descriptor, fieldNumbersToHere);
            }
        });

        connect(this, &QTreeWidget::currentItemChanged, [this, row_widget, field_descriptor, fieldNumbersToHere](QTreeWidgetItem *item) {
          if (item == row_widget) {
              emit fieldSelected(field_descriptor, fieldNumbersToHere);
          }
        });


        // do some nice recursion for the children of this item
        auto child_descriptor = field_descriptor->message_type();
        if (child_descriptor) {
            add_filter_descriptor(child_descriptor, fieldNumbersToHere, row_widget);
        }
    }
}