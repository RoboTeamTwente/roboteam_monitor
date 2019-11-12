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
  QWidget * create_series_overview_widget(QHBoxLayout *dialog_horizontal_layout);
  void initialize_layout();
};

#endif //RTT_CHARTVIEW_H
