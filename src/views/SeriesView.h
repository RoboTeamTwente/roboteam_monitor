//
// Created by Lukas Bos on 13/11/2019.
//

#ifndef RTT_SERIESVIEW_H
#define RTT_SERIESVIEW_H

#include <src/presenters/ChartPresenter.h>
#include <QGroupBox>
#include <unordered_map>
#include "FilterView.h"

class SeriesView : public QGroupBox {
 private:
  SeriesPresenter * seriesModel;

 public:
  SeriesView(SeriesPresenter * series_presenter);
};

#endif //RTT_SERIESVIEW_H
