#ifndef RTT_CHARTMODEL_H
#define RTT_CHARTMODEL_H

#include "src/models/SeriesModel.h"
#include <vector>
#include <roboteam_utils/Vector2.h>
#include <qglobal.h>
#include <QtCharts/QtCharts>

class SeriesModel;
class SeriesPresenter;
class ChartModel {

  // Presenter definition
  friend class ChartPresenter;

  // Properties
  bool darkTheme = true;
  qreal min_x = 9e99;
  qreal min_y = 9e99;
  qreal max_x = -9e99;
  qreal max_y = -9e99;

  QValueAxis * xAxis = nullptr;
  QValueAxis * yAxis = nullptr;
  long time_chart_created;

  bool sliding_window = true;
  qreal sliding_window_width = 10.0;
  qreal margin_y = 10.0;
  qreal margin_x = 10.0;
  int update_frequency = 5;

  // Relationships
  std::vector<SeriesPresenter *> seriesList;

 public:
  ChartModel();
};

#endif //RTT_CHARTMODEL_H
