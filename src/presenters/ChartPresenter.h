#ifndef RTT_CHARTPRESENTER_H
#define RTT_CHARTPRESENTER_H

#include <QObject>
#include <QtCharts/QtCharts>
#include <roboteam_utils/json.hpp>

using json = nlohmann::json;

class SeriesPresenter;
class ChartModel;
class SeriesModel;
class ChartPresenter : public QObject {
 Q_OBJECT
 private:
  ChartModel *model;

 public:
  explicit ChartPresenter(ChartModel *model);
  json to_json();

 public slots:
  void add_new_series();
  void delete_series(SeriesPresenter *series_to_delete);
  void set_theme(bool dark_theme);
  void adjustBoundaries(const qreal & x, const qreal & y, const qreal & margin);
  void resetBoundaries();
  qreal get_min_x();
  qreal get_min_y();
  qreal get_max_x();
  qreal get_max_y();
  bool is_sliding_window() const;
  void set_sliding_window(bool sliding_window);
  qreal get_sliding_window_width() const;
  void set_sliding_window_width(qreal sliding_window_width);
  qreal get_margin_y() const;
  void set_margin_y(qreal margin_y);
  qreal get_margin_x() const;
  void set_margin_x(qreal margin_x);
  int get_update_frequency() const;
  void set_update_frequency(int update_frequency);
  std::vector<SeriesPresenter *> get_series_list();
  void apply_data();
  void clear_data();

  QValueAxis * getxAxis();
  QValueAxis * getyAxis();

  long get_time_chart_created();

  void setxAxis(QValueAxis *);
  void setyAxis(QValueAxis *);

 signals:
  void seriesAdded(SeriesPresenter *series);
  void seriesRemoved(SeriesPresenter *series);
  void themeChanged(bool darkTheme);
  void chartBoundariesChanged();
  void update_frequency_changed(int update_frequency);
  void set_sliding_window_changed(bool use_sliding_window);
};

#endif //RTT_CHARTPRESENTER_H
