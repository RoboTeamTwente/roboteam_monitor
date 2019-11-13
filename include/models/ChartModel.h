#ifndef RTT_CHARTMODEL_H
#define RTT_CHARTMODEL_H

#include <QObject>

class ChartSeries;
class ChartModel : public QObject {
  Q_OBJECT
 private:
  std::vector<ChartSeries *> seriesList;
  bool darkTheme = true;

 public:
  explicit ChartModel();

 public slots:
  void add_new_series();
  void delete_series(ChartSeries * series_to_delete);
  void set_theme(bool dark_theme);

  signals:
    void seriesAdded(ChartSeries * series);
    void seriesRemoved(ChartSeries * series);
    void themeChanged(bool darkTheme);
};

#endif //RTT_CHARTMODEL_H
