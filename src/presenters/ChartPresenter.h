#ifndef RTT_CHARTPRESENTER_H
#define RTT_CHARTPRESENTER_H

#include <QObject>
#include <QtCharts/QtCharts>
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
  void delete_series(SeriesPresenter *series_to_delete);
  void set_theme(bool dark_theme);
  void adjustBoundaries(const qreal & x, const qreal & y);
  qreal get_min_x();
  qreal get_min_y();
  qreal get_max_x();
  qreal get_max_y();

  QValueAxis * getxAxis();
  QValueAxis * getyAxis();


  void setxAxis(QValueAxis *);
  void setyAxis(QValueAxis *);

 signals:
  void seriesAdded(SeriesPresenter *series);
  void seriesRemoved(SeriesPresenter *series);
  void themeChanged(bool darkTheme);
  void chartBoundariesChanged();
};

#endif //RTT_CHARTPRESENTER_H
