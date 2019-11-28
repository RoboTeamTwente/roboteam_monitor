//
// Created by Lukas Bos on 27/11/2019.
//

#include <src/presenters/SeriesPresenter.h>
#include <src/presenters/SeriesSettingsPresenter.h>
#include <roboteam_proto/Subscriber.h>


#include "SubscriptionManager.h"


void SubscriptionManager::reconfigure_ip(const QString &ip_config) {
    delete robot_command_subscriber;
    delete world_subscriber;
    delete geometry_subscriber;

    setup_subscriptions(ip_config);
}

void SubscriptionManager::setup_subscriptions(const QString & ip_config) {
    std::string ip = ip_config.toStdString();
    robot_command_subscriber = new proto::Subscriber<proto::RobotCommand>(proto::ROBOT_COMMANDS_PRIMARY_CHANNEL,
                                                                          &SubscriptionManager::handle_robot_command,
                                                                          this,
                                                                          ip);

    world_subscriber = new proto::Subscriber<proto::World>(proto::WORLD_CHANNEL,
                                                           &SubscriptionManager::handle_world_msg, this, ip);

    geometry_subscriber = new proto::Subscriber<proto::SSL_GeometryData>(proto::GEOMETRY_CHANNEL,
                                                                         &SubscriptionManager::handle_geom_msg,
                                                                         this,
                                                                         ip);
}

void SubscriptionManager::register_series(SeriesPresenter *series_model) {
    series.insert(series_model);
}

void SubscriptionManager::remove_series(SeriesPresenter *series_model) {
    series.erase(std::find(series.begin(), series.end(), series_model));
}

std::set<SeriesPresenter *> SubscriptionManager::get_series_for_channel(proto::ChannelType channel_type) {
    std::set<SeriesPresenter *> series_with_valid_channel;
    for (auto s : series) {
        if (s->getSettings()->get_channel_type() == channel_type) {
            series_with_valid_channel.insert(s);
        }
    }
    return series_with_valid_channel;
}

template<class T>
void SubscriptionManager::propagate_msg(T msg, proto::ChannelType channel_type) {
    for (auto series : get_series_for_channel(channel_type)) {
        series->handle_incoming_message(&msg);
    }
}

void SubscriptionManager::handle_robot_command(proto::RobotCommand & msg) {
    propagate_msg(msg, proto::ROBOT_COMMANDS_PRIMARY_CHANNEL);
}

void SubscriptionManager::handle_world_msg(proto::World & msg) {
    propagate_msg(msg, proto::WORLD_CHANNEL);
}

void SubscriptionManager::handle_geom_msg(proto::SSL_GeometryData & msg) {
    propagate_msg(msg, proto::GEOMETRY_CHANNEL);
}








