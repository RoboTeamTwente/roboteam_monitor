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
class ChartModel {

  // Presenter definition
  friend class ChartPresenter;

  // Properties
  bool darkTheme = true;
  bool sliding_window = true;
  qreal sliding_window_width = 10.0;
  qreal margin_y = 10.0;
  qreal margin_x = 10.0;
  int update_frequency = 5;

  // Relationships
  std::vector<SeriesPresenter *> seriesList;

  // Variables for use during execution
  qreal min_x = 0;
  qreal min_y = 0;
  qreal max_x = 1;
  qreal max_y = 1;
  QValueAxis * xAxis = nullptr;
  QValueAxis * yAxis = nullptr;
  long time_chart_created;

 public:
  ChartModel();
  json to_json();
};

#endif //RTT_CHARTMODEL_H
