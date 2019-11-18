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
  qreal max_x = 1.0;
  qreal max_y = 1.0;

  QValueAxis * xAxis = nullptr;
  QValueAxis * yAxis = nullptr;

  // Relationships
  std::vector<SeriesPresenter *> seriesList;

 public:
  ChartModel();
};

#endif //RTT_CHARTMODEL_H
