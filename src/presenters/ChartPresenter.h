#ifndef RTT_CHARTPRESENTER_H
#define RTT_CHARTPRESENTER_H

#include <QObject>

class SeriesPresenter;
class ChartModel;
class SeriesModel;
class ChartPresenter : public QObject {
 Q_OBJECT
 private:
  ChartModel *model;

 public:
  explicit ChartPresenter(ChartModel *model);

 public slots:
  void add_new_series();
  void delete_series(SeriesModel *series_to_delete);
  void set_theme(bool dark_theme);

 signals:
  void seriesAdded(SeriesModel *series);
  void seriesRemoved(SeriesModel *series);
  void themeChanged(bool darkTheme);
};

#endif //RTT_CHARTPRESENTER_H
