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
  bool is_dark_theme() const;
  void set_dark_theme(bool dark_theme);
  const std::vector<SeriesPresenter *> &get_series_list() const;
  void set_series_list(const std::vector<SeriesPresenter *> &series_list);
};

#endif //RTT_CHARTMODEL_H
