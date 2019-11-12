//
// Created by Lukas Bos on 11/11/2019.
//

#ifndef RTT_SELECTTYPEWIDGET_H
#define RTT_SELECTTYPEWIDGET_H

#include <QTreeWidget>
#include <google/protobuf/descriptor.h>

class SelectTypeWidget : public QTreeWidget {
  Q_OBJECT
 public:
    explicit SelectTypeWidget(QDialog * parent);
 private:
  QDialog * parent_widget = nullptr;
  QTreeWidgetItem * top_level_tree_item;
  void add_filter_descriptor(const google::protobuf::Descriptor * descriptor, int depth, QTreeWidgetItem * parent);
 public slots:
  void update_filters_layout(const QString & topic_name);

  signals:
    void fieldSelected(const google::protobuf::FieldDescriptor * field_descriptor);
};

#endif //RTT_SELECTTYPEWIDGET_H
