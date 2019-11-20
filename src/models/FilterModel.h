#ifndef RTT_FILTERMODEL_H
#define RTT_FILTERMODEL_H

#include <QString>
#include <src/presenters/SeriesPresenter.h>

class SeriesPresenter;
class SeriesSettingsPresenter;
class FilterModel {

  // Presenter
  friend class FilterPresenter;

  // properties
  FieldDefinition * field_definition = nullptr;
  google::protobuf::Message * reference_message = nullptr;
  QString value;

  // Relations
  SeriesSettingsPresenter * parent;

 public:
  FilterModel(SeriesSettingsPresenter * parent);
  FilterModel(SeriesSettingsPresenter * parent,
              FieldDefinition * field_definition,
              google::protobuf::Message *reference_message,
              QString value);


  // methods
  bool operator==(const FilterModel & other);
};
#endif //RTT_FILTERMODEL_H
