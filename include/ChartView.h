//
// Created by Lukas Bos on 18/10/2019.
//

#ifndef RTT_CHARTVIEW_H
#define RTT_CHARTVIEW_H

#include <QWidget>
#include <QCheckBox>
#include <QtCharts/QtCharts>

class ChartSeries;
class ChartView : public QWidget {
 public:
  explicit ChartView(QWidget * parent = nullptr);
 public slots:
  void add_new_series();
  void delete_series(ChartSeries * series_to_delete);
  void set_theme(bool dark_theme);
 private:
  std::vector<ChartSeries *> all_series;
  QVBoxLayout * series_overview_layout;
  QChartView * chart;
  QCheckBox * theme_checkbox;
};

#endif //RTT_CHARTVIEW_H
