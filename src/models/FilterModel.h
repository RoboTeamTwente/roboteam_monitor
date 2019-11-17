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
  google::protobuf::FieldDescriptor * field_descriptor;
  google::protobuf::Message * reference_message;
  QString value;

  // Relations
  SeriesSettingsPresenter * parent;

 public:
  FilterModel(SeriesSettingsPresenter * parent);
  FilterModel(SeriesSettingsPresenter * parent,
              google::protobuf::FieldDescriptor *field_descriptor,
              google::protobuf::Message *reference_message,
              QString value);


  // methods
  bool operator==(const FilterModel & other);
};
#endif //RTT_FILTERMODEL_H
