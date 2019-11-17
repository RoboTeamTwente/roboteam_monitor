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

class ChartPresenter;
class SeriesInputSettingsModel;
class SeriesModel {
  friend class SeriesPresenter;
 public:
  SeriesModel(ChartPresenter * parent);
  SeriesModel(ChartPresenter * parent, QString name = "series");
 private:
  // properties
  QXYSeries * qt_series = nullptr;
  void * proto_subscriber = nullptr;

  // relationships
  ChartPresenter * parent = nullptr;
 public:
  ChartPresenter *get_parent() const;
 private:
  SeriesInputSettingsModel * settings;


  void init_subscriber_for_channel_type(const proto::ChannelType & channel_type);
  void handle_robot_command_input(proto::RobotCommand & robot_command);
  void handle_world_input(proto::World & world);
  void handle_feedback_input(proto::RobotFeedback & feedback);
  void handle_setting_input(proto::Setting & setting);

  template <class T>
  void handle_incoming_message(T message, const google::protobuf::Reflection & reflection);

};

#endif //RTT_SERIESMODEL_H
