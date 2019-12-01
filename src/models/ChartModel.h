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
  int update_frequency = 4;
  QString ip_config = "127.0.0.1";

  // Relationships
  std::vector<SeriesPresenter *> seriesList;

 public:
  ChartModel() = default;
};

#endif //RTT_CHARTMODEL_H
