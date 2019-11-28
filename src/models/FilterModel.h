#ifndef RTT_FILTERMODEL_H
#define RTT_FILTERMODEL_H

#include <roboteam_utils/json.hpp>
#include <QString>
#include <src/presenters/SeriesPresenter.h>

using json = nlohmann::json;

class SeriesPresenter;
class FilterModel {

  // Presenter
  friend class FilterPresenter;

  // properties
  FieldDefinition * field_definition = nullptr;
  QString value;

 public:
  FilterModel() = default;
  FilterModel(FieldDefinition * field_definition, QString value);
  FilterModel(json data);


  // methods
  bool operator==(const FilterModel & other);
  json to_json();
};
#endif //RTT_FILTERMODEL_H
