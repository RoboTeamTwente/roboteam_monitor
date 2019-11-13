#ifndef RTT_CHARTVIEW_H
#define RTT_CHARTVIEW_H

#include <QWidget>
#include <QCheckBox>
#include <QtCharts/QtCharts>
#include <src/models/ChartModel.h>

class ChartSeries;
class ChartView : public QWidget {
 public:
  explicit ChartView(ChartModel * model, QWidget * parent = nullptr);
};

#endif //RTT_CHARTVIEW_H
