#ifndef RTT_SERIESMODEL_H
#define RTT_SERIESMODEL_H

#include <string>
#include <QtCharts/QtCharts>
#include <QWidget>
#include <roboteam_proto/Subscriber.h>
#include <roboteam_proto/RobotFeedback.pb.h>
#include <roboteam_proto/RobotCommand.pb.h>
#include <roboteam_proto/World.pb.h>
#include <roboteam_proto/Setting.pb.h>
#include <roboteam_utils/Timer.h>
#include <src/models/FilterModel.h>
#include <src/views/SeriesView.h>
#include "SeriesInputSettingsModel.h"

class ChartModel;
class SeriesModel : public QObject {
  Q_OBJECT
 private:
  ChartModel * parent = nullptr;
  SeriesInputSettingsModel * settingsModel;
  QXYSeries * qt_series = nullptr;
  void * proto_subscriber = nullptr;

  void init_subscriber_for_channel_type(const proto::ChannelType & channel_type);
  void handle_robot_command_input(proto::RobotCommand & robot_command);
  void handle_world_input(proto::World & world);
  void handle_feedback_input(proto::RobotFeedback & feedback);
  void handle_setting_input(proto::Setting & setting);

  template <class T>
  void handle_incoming_message(T message, const google::protobuf::Reflection & reflection);

 public:
  explicit SeriesModel(ChartModel * chartModel, const QString & title);
  QXYSeries * get_qt_series();
  void set_name(const QString &name);
  ChartModel *get_parent() const;
  void set_parent(ChartModel *parent);
  SeriesInputSettingsModel *get_settings_model() const;
  void set_settings_model(SeriesInputSettingsModel *settings_model);

 public slots:
  void set_color(const QColor & color);
  void set_visible(bool visible);
};

#endif //RTT_SERIESMODEL_H
