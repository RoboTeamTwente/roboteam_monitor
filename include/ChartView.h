//
// Created by Lukas Bos on 13/11/2019.
//

#ifndef RTT_CHARTVIEW_H
#define RTT_CHARTVIEW_H

#include <QWidget>
#include "ChartModel.h"
class ChartView : public QWidget {
 private:
  ChartModel * model;
 public:
  ChartView(ChartModel *model, QWidget  * parent = nullptr);
};

#endif //RTT_CHARTVIEW_H
