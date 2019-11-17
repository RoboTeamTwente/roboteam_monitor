#ifndef RTT_CHARTMODEL_H
#define RTT_CHARTMODEL_H

#include "src/models/SeriesModel.h"
#include <vector>

class SeriesModel;
class SeriesPresenter;
class ChartModel {

  // Presenter definition
  friend class ChartPresenter;

  // Properties
  bool darkTheme = true;

  // Relationships
  std::vector<SeriesPresenter *> seriesList;

 public:
  ChartModel();
};

#endif //RTT_CHARTMODEL_H
