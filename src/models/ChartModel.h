#ifndef RTT_CHARTMODEL_H
#define RTT_CHARTMODEL_H

#include "SeriesModel.h"

struct ChartModel {
  // properties
  bool darkTheme = true;

  // relationships
  std::vector<SeriesModel *> seriesList = {};
};

#endif //RTT_CHARTMODEL_H
