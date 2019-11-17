#ifndef RTT_SERIESPRESENTER_H
#define RTT_SERIESPRESENTER_H

#include <string>
#include <QtCharts/QtCharts>
#include <QWidget>

#include <roboteam_utils/Timer.h>
#include <src/presenters/FilterPresenter.h>
#include <src/views/SeriesView.h>
#include "src/presenters/SeriesInputSettingsPresenter.h"

class ChartPresenter;
class SeriesInputSettingsPresenter;
class SeriesModel;
class SeriesPresenter : public QObject {
  Q_OBJECT
 private:
  SeriesModel * model;

 public:
  explicit SeriesPresenter(SeriesModel * model);
  QXYSeries * get_qt_series();
  void set_name(const QString &name);
  SeriesInputSettingsPresenter * getSettings();

 public slots:
  void set_color(const QColor & color);
  void set_visible(bool visible);
};

#endif //RTT_SERIESPRESENTER_H
