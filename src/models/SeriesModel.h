#ifndef RTT_SERIESMODEL_H
#define RTT_SERIESMODEL_H

#include "ChartModel.h"
#include <QString>
#include <roboteam_proto/Channels.h>
#include <roboteam_proto/Subscriber.h>
#include <roboteam_proto/RobotFeedback.pb.h>
#include <roboteam_proto/RobotCommand.pb.h>
#include <roboteam_proto/World.pb.h>
#include <roboteam_proto/Setting.pb.h>
#include <QtCharts/QtCharts>
#include <roboteam_utils/Timer.h>

class ChartPresenter;
class SeriesSettingsModel;
class SeriesSettingsPresenter;
class SeriesModel {
  friend class SeriesPresenter;
 public:
  SeriesModel(ChartPresenter * parent, const QString & name = "Series");
 private:
  // properties
  QXYSeries * qt_series = nullptr;
  void * proto_subscriber = nullptr;
  QVector<QPointF> * data = nullptr;

  // relationships
  ChartPresenter * parent = nullptr;
 public:
  ChartPresenter *get_parent() const;

 private:
  roboteam_utils::Timer timer;
  int rate = 0;
  int internal_rate = 0;
  long lastRateUpdateTime;
  long time_since_series_is_created;



 private:

  SeriesSettingsPresenter * settings_presenter = nullptr;
  void init_subscriber_for_channel_type(const proto::ChannelType & channel_type);

  template <class T>
  void handle_incoming_message(T message);

  void determine_packet_rate();
};

#endif //RTT_SERIESMODEL_H
