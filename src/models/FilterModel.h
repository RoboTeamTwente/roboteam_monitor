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
  QString value;

  // Relations
  SeriesSettingsPresenter * parent;

 public:
  FilterModel(const FilterModel & model, SeriesSettingsPresenter * parent);
  FilterModel(SeriesSettingsPresenter * parent);
  FilterModel(SeriesSettingsPresenter * parent,
              FieldDefinition * field_definition,
              QString value);
  FilterModel(SeriesSettingsPresenter * parent, json data);


  // methods
  bool operator==(const FilterModel & other);
  json to_json();
};
#endif //RTT_FILTERMODEL_H
