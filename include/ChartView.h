//
// Created by Lukas Bos on 18/10/2019.
//

#ifndef RTT_CHARTVIEW_H
#define RTT_CHARTVIEW_H

#include <QWidget>
#include "ChartSeries.h"

class ChartView : public QWidget {
 public:
  explicit ChartView(QWidget * parent = nullptr);
 public slots:
  void add_new_series();
  void delete_series(ChartSeries * series_to_delete);
 private:
  std::vector<std::shared_ptr<ChartSeries>> all_series;
  QVBoxLayout * series_overview_layout;
};

#endif //RTT_CHARTVIEW_H
