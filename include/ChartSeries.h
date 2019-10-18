//
// Created by Lukas Bos on 18/10/2019.
//

#ifndef RTT_CHARTSERIES_H
#define RTT_CHARTSERIES_H

#include <string>
#include <QtCharts/QtCharts>
#include <QWidget>

class MainWindow;
class ChartView;
class QLineEdit;
class QPushButton;
class ChartSeries : public QWidget {
 private:
  std::string name;
  QLineSeries qt_series;

  QLineEdit * series_title_line_edit;
  QPushButton * delete_series_button;
 public:
  explicit ChartSeries(ChartView * chart_view);
  const std::string &getName() const;
  void setName(const std::string &name);
};

#endif //RTT_CHARTSERIES_H
