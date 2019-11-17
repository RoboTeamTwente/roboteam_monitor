#ifndef RTT_CHARTMODEL_H
#define RTT_CHARTMODEL_H

#include "src/models/SeriesModel.h"
#include <vector>

class SeriesModel;
class ChartModel {
  friend class ChartPresenter;
  // properties
  bool darkTheme = true;

  // relationships
  std::vector<SeriesModel *> seriesList;
 public:
  ChartModel();
  bool is_dark_theme() const;
  void set_dark_theme(bool dark_theme);
  const std::vector<SeriesModel *> &get_series_list() const;
  void set_series_list(const std::vector<SeriesModel *> &series_list);
};

#endif //RTT_CHARTMODEL_H
