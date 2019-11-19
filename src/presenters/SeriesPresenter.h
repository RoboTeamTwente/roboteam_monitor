#ifndef RTT_SERIESPRESENTER_H
#define RTT_SERIESPRESENTER_H

#include <string>
#include <QtCharts/QtCharts>
#include <QWidget>

#include <roboteam_utils/Timer.h>
#include <src/presenters/FilterPresenter.h>
#include <src/views/SeriesView.h>
#include "src/presenters/SeriesSettingsPresenter.h"

class ChartPresenter;
class SeriesSettingsPresenter;
class SeriesModel;
class SeriesPresenter : public QObject {
  Q_OBJECT
 private:
  SeriesModel * model;

 public:
  explicit SeriesPresenter(SeriesModel * model);
  QXYSeries * get_qt_series();
  void set_name(const QString &name);
  SeriesSettingsPresenter * getSettings();
  ChartPresenter * getParent();
  int get_rate();

 public slots:
  void set_color(const QColor & color);
  void set_visible(bool visible);
  void start_new_subscription();
};

#endif //RTT_SERIESPRESENTER_H
