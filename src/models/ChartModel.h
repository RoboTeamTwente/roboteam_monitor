#ifndef RTT_CHARTMODEL_H
#define RTT_CHARTMODEL_H

#include <roboteam_utils/json.hpp>
#include "src/presenters/SeriesPresenter.h"
#include <vector>
#include <qglobal.h>
#include <QtCharts/QtCharts>

using json = nlohmann::json;

class SeriesModel;
class SeriesPresenter;
class ChartPresenter;
class ChartModel {

  // Presenter definition
  friend class ChartPresenter;

  // Properties
  bool darkTheme = true;
  bool sliding_window = true;
  qreal sliding_window_width = 10000.0;
  qreal margin_y = 10.0;
  qreal margin_x = 100.0;
  int update_frequency = 5;
  QString ip_config = "130.89.139.223";

  // Relationships
  std::vector<SeriesPresenter *> seriesList;

 public:
  ChartModel();
  explicit ChartModel(ChartPresenter * presenter, json data);
  json to_json();
};

#endif //RTT_CHARTMODEL_H
