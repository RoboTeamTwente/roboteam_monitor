#ifndef RTT_SERIESINPUTSETTINGSMODEL_H
#define RTT_SERIESINPUTSETTINGSMODEL_H

#include <vector>
#include <roboteam_proto/Channels.h>
#include "src/presenters/FilterPresenter.h"
#include "src/presenters/SeriesPresenter.h"

struct SeriesInputSettingsModel {
  friend class SeriesInputSettingsPresenter;

  explicit SeriesInputSettingsModel() = default;

  // properties
  std::vector<FilterPresenter *> filters = {};
  proto::ChannelType channel_type = proto::UNDEFINED_CHANNEL;
  std::vector<FilterPresenter *> get_filters();
  void set_filters(const std::vector<FilterPresenter *> &filters);
  proto::ChannelType get_channel_type() const;
  void set_channel_type(proto::ChannelType channel_type);
  SeriesPresenter *get_parent() const;
  void set_parent(SeriesPresenter *parent);

  // relationships
  SeriesPresenter * parent = nullptr;
};

#endif //RTT_SERIESINPUTSETTINGSMODEL_H
