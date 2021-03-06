#ifndef RTT_SERIESPRESENTER_H
#define RTT_SERIESPRESENTER_H

#include <string>
#include <QtCharts/QtCharts>
#include <QWidget>

#include <roboteam_utils/Timer.h>
#include <src/presenters/FilterPresenter.h>
#include <src/views/SeriesView.h>

class ChartPresenter;
class SeriesSettingsPresenter;
class SeriesModel;
class SeriesPresenter : public QObject {
  Q_OBJECT
 private:
  SeriesModel * model;


  // properties
  QXYSeries * qt_series = nullptr;
  QList<QPointF> * data = nullptr;

  roboteam_utils::Timer timer;
  int rate = 0;
  int filtered_packets = 0;
  int internal_rate = 0;
  int internal_filtered_packets = 0;
  long lastRateUpdateTime;
  long time_since_series_is_created = 0;


  void determine_packet_rate();

 public:
  explicit SeriesPresenter(SeriesModel * model);
  ~SeriesPresenter();
  json to_json();

  void handle_incoming_message(google::protobuf::Message * message);

  QXYSeries * get_qt_series();
  void set_name(const QString &name);
  SeriesSettingsPresenter * getSettings();
  SeriesSettingsPresenter * get_settings_copy();
  void applySettings(SeriesSettingsPresenter * new_settings);
  void apply_data();
  void clear_data();
  void reboot_subscriber();

  bool message_is_filtered(google::protobuf::Message * message);

  ChartPresenter * getParent();
  int get_rate();
  int get_filtered_packets_rate();

 public slots:
  void set_color(const QColor & color);
  void set_visible(bool visible);
  void start_new_subscription();

};

#endif //RTT_SERIESPRESENTER_H
