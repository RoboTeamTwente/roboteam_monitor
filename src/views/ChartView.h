//
// Created by Lukas Bos on 13/11/2019.
//

#ifndef RTT_CHARTVIEW_H
#define RTT_CHARTVIEW_H

#include <QWidget>
#include "src/presenters/ChartPresenter.h"
#include "SeriesView.h"
#include <unordered_map>

class ChartView : public QWidget {
 private:
  ChartPresenter * presenter;
  std::unordered_map<SeriesModel *, SeriesView *> seriesMap;

 public:
  ChartView(ChartPresenter *model, QWidget  * parent = nullptr);
};

#endif //RTT_CHARTVIEW_H
