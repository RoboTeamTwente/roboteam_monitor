#ifndef RTT_SERIESINPUTSETTINGSMODEL_H
#define RTT_SERIESINPUTSETTINGSMODEL_H

#include <vector>
#include <roboteam_proto/Channels.h>
#include "src/presenters/FilterPresenter.h"
#include "src/presenters/SeriesPresenter.h"

class SeriesInputSettingsModel {
  friend class SeriesInputSettingsPresenter;


  // properties
  std::vector<FilterPresenter *> filters = {};
  proto::ChannelType channel_type = proto::UNDEFINED_CHANNEL;

  // relationships
  SeriesPresenter * parent = nullptr;

 public:
  explicit SeriesInputSettingsModel() = default;

};

#endif //RTT_SERIESINPUTSETTINGSMODEL_H
