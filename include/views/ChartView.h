//
// Created by Lukas Bos on 13/11/2019.
//

#ifndef RTT_CHARTVIEW_H
#define RTT_CHARTVIEW_H

#include <QWidget>
#include "include/models/ChartModel.h"
#include "SeriesView.h"
#include <map>

class ChartView : public QWidget {
 private:
  ChartModel * model;
  std::map<SeriesModel *, SeriesView *> seriesMap;

 public:
  ChartView(ChartModel *model, QWidget  * parent = nullptr);
};

#endif //RTT_CHARTVIEW_H
