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
#include <src/Filter.h>
#include <include/views/SeriesView.h>

class ChartModel;
class SeriesModel : public QObject {
 private:

  // relations
  SeriesView * view;

 public:
  SeriesView *get_view() const;
  void set_view(SeriesView *view);
 private:
  QXYSeries * qt_series = nullptr;
  proto::ChannelType channel_type;
  void * proto_subscriber = nullptr;
  std::vector<Filter *> filters;

  void init_subscriber_for_channel_type(const proto::ChannelType & channel_type);
  void handle_robot_command_input(proto::RobotCommand & robot_command);
  void handle_world_input(proto::World & world);
  void handle_feedback_input(proto::RobotFeedback & feedback);
  void handle_setting_input(proto::Setting & setting);

  template <class T>
  void handle_incoming_message(T message, const google::protobuf::Reflection & reflection);

 public:
  explicit SeriesModel(ChartModel * chartModel);
  QXYSeries * get_qt_series();
  void set_name(const QString &name);
  void update_channel(const proto::ChannelType & channel_type);

 public slots:
  void set_color(const QColor & color);
  void set_change_color_button_background(const QColor & color) const;
  void set_visible(bool visible);
  Filter * add_new_filter();
  void removeFilter(Filter * filter_to_remove);
  const std::vector<Filter *> & get_filters();
};

#endif //RTT_SERIESMODEL_H
