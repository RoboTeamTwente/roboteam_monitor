//
// Created by Lukas Bos on 13/11/2019.
//

#ifndef RTT_SERIESVIEW_H
#define RTT_SERIESVIEW_H

#include <include/models/ChartModel.h>
#include <QGroupBox>
class SeriesView : public QGroupBox {
 private:
  SeriesModel * seriesModel;
 public:
  SeriesView(SeriesModel * seriesModel);
};

#endif //RTT_SERIESVIEW_H
