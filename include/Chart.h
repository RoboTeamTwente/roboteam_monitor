#ifndef RTT_CHART_H
#define RTT_CHART_H

#include <QWidget>
#include <QCheckBox>
#include <QtCharts/QtCharts>

class ChartSeries;
class Chart : public QWidget {
  Q_OBJECT
 private:
  std::vector<ChartSeries *> seriesList;
  bool darkTheme = true;

 public:
  explicit Chart(QWidget * parent = nullptr);
  void drawView();

 public slots:
  void add_new_series();
  void delete_series(ChartSeries * series_to_delete);
  void set_theme(bool dark_theme);

  signals:
    void seriesAdded(ChartSeries * series);
    void seriesRemoved(ChartSeries * series);
    void themeChanged(bool darkTheme);
};

#endif //RTT_CHART_H
