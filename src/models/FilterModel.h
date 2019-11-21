#ifndef RTT_FILTERMODEL_H
#define RTT_FILTERMODEL_H

#include <roboteam_utils/json.hpp>
#include <QString>
#include <src/presenters/SeriesPresenter.h>

using json = nlohmann::json;

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
  json to_json();
};
#endif //RTT_FILTERMODEL_H
