//
// Created by Lukas Bos on 11/11/2019.
//

#ifndef RTT_SELECTTYPEWIDGET_H
#define RTT_SELECTTYPEWIDGET_H

#include <QTreeWidget>
#include <google/protobuf/descriptor.h>
#include <src/models/FieldDefinition.h>

class AddFilterDialog;
class SelectTypeWidget : public QTreeWidget {
  Q_OBJECT
 public:
    explicit SelectTypeWidget(AddFilterDialog * parent);
 private:
  AddFilterDialog * parent_widget = nullptr;
  QTreeWidgetItem * top_level_tree_item;
  void add_filter_descriptor(const google::protobuf::Descriptor * descriptor, const std::vector<int> & field_numbers, const QString & name, QTreeWidgetItem * parent);
 public slots:
  void update_filters_layout(const QString & topic_name);

  signals:
    void fieldSelected(FieldDefinition * field_definition);
    void fieldSelectedAndClose(FieldDefinition * field_definition);

};

#endif //RTT_SELECTTYPEWIDGET_H
