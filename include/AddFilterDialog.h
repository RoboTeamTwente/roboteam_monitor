//
// Created by Lukas Bos on 11/11/2019.
//

#ifndef RTT_ADDFILTERDIALOG_H
#define RTT_ADDFILTERDIALOG_H

#include <QDialog>
#include <include/SelectTypeWidget.h>

class AddFilterDialog : public QDialog {
 Q_OBJECT
 private:
  const google::protobuf::FieldDescriptor *selectedFieldDescriptor = nullptr;
  SelectTypeWidget *filters_tree_widget;
 public:
  explicit AddFilterDialog(QWidget *parent = nullptr);
 public slots:
  void set_selected_field_descriptor(const google::protobuf::FieldDescriptor *selected_field_descriptor);
  void update_filters_layout(const QString &topic_name);
 signals:
  void valueChanged(const google::protobuf::FieldDescriptor *selected_field_descriptor);
};

#endif //RTT_ADDFILTERDIALOG_H
