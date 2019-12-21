/*
 *
 * Roboteam_monitor by default subscribes to everything.
 * In this way it only needs as many topics as necessary. e.g. not more than necessary.
 */

#ifndef RTT_SUBSCRIPTIONMANAGER_H
#define RTT_SUBSCRIPTIONMANAGER_H

#include <roboteam_proto/Channels.h>
#include <roboteam_proto/Subscriber.h>
#include <vector>
#include <roboteam_proto/messages_robocup_ssl_geometry.pb.h>
#include <roboteam_proto/RobotCommand.pb.h>
#include <roboteam_proto/World.pb.h>

class SeriesPresenter;
class SubscriptionManager {
 public:
  SubscriptionManager() = default;
  void register_series(SeriesPresenter * series_model);
  void remove_series(SeriesPresenter * series_model);
  void reconfigure_ip(const QString & ip_config);
  void setup_subscriptions(const QString & ip_config);

 private:
    std::set<SeriesPresenter *> series;
    std::set<SeriesPresenter *> get_series_for_channel(proto::ChannelType channel_type);

    proto::Subscriber<proto::RobotCommand> * robot_command_subscriber = nullptr;
    void handle_robot_command(proto::RobotCommand &);

    proto::Subscriber<proto::World> * world_subscriber = nullptr;
    void handle_world_msg(proto::World &);

    proto::Subscriber<proto::SSL_GeometryData> * geometry_subscriber = nullptr;
    void handle_geom_msg(proto::SSL_GeometryData &);


    template <class T>
    void propagate_msg(T msg, proto::ChannelType channel_type);

};

#endif //RTT_SUBSCRIPTIONMANAGER_H
