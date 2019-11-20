#ifndef RTT_FILTERPRESENTER_H
#define RTT_FILTERPRESENTER_H

#include <google/protobuf/descriptor.h>
#include <QString>
#include <QObject>
#include <src/models/FieldDefinition.h>

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
  void set_field_definition(FieldDefinition * field_definition);
  FieldDefinition * get_field_definition();
  bool operator==(const FilterPresenter &rhs) const;
  bool operator!=(const FilterPresenter &rhs) const;
  const QString &get_value();

  signals:
    void value_changed(const QString & value);
    void field_definition_changed(FieldDefinition * fd);
};

#endif //RTT_FILTERPRESENTER_H
