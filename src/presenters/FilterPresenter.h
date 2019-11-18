#ifndef RTT_FILTERPRESENTER_H
#define RTT_FILTERPRESENTER_H

#include <google/protobuf/descriptor.h>
#include <QString>
#include <QObject>

class SeriesSettingsPresenter;
class FilterModel;
class FilterPresenter : public QObject {
  Q_OBJECT
 private:
  FilterModel * model;
 public:
  FilterModel *get_model() const;
 public:
  explicit FilterPresenter(FilterModel * model);
  SeriesSettingsPresenter * getParent();
  void set_value(const QString & value);
  void set_field_descriptor(google::protobuf::FieldDescriptor * fd);
  const google::protobuf::FieldDescriptor * get_field_descriptor();
  bool operator==(const FilterPresenter &rhs) const;
  bool operator!=(const FilterPresenter &rhs) const;
  const QString &get_value();

  signals:
    void value_changed(const QString & value);
    void field_descriptor_changed(google::protobuf::FieldDescriptor * fd);
};

#endif //RTT_FILTERPRESENTER_H
