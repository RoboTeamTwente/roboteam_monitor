#ifndef RTT_SERIESINPUTSETTINGSMODEL_H
#define RTT_SERIESINPUTSETTINGSMODEL_H

#include <vector>
#include <roboteam_proto/Channels.h>
#include "FilterModel.h"
#include "SeriesModel.h"

struct SeriesInputSettingsModel {
  explicit SeriesInputSettingsModel() = default;

  // properties
  std::vector<FilterModel> filters = {};
  proto::ChannelType channel_type = proto::UNDEFINED_CHANNEL;

  // relationships
  SeriesModel * parent = nullptr;
};

#endif //RTT_SERIESINPUTSETTINGSMODEL_H
