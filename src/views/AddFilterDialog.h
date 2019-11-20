//
// Created by Lukas Bos on 11/11/2019.
//

#ifndef RTT_ADDFILTERDIALOG_H
#define RTT_ADDFILTERDIALOG_H

#include <QDialog>
#include <src/views/components/SelectTypeWidget.h>

class AddFilterDialog : public QDialog {
 Q_OBJECT
 private:
  FieldDefinition *selected_field_definition = nullptr;
  SelectTypeWidget *filters_tree_widget;
 public:
  explicit AddFilterDialog(QWidget *parent = nullptr);
 public slots:
  void set_selected_field_definition(FieldDefinition * field_definition);
  void update_filters_layout(const QString &topic_name);
 signals:
  void valueChanged(FieldDefinition * field_definition);
};

#endif //RTT_ADDFILTERDIALOG_H
