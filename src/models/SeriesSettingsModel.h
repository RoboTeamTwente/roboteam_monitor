#ifndef RTT_SERIESSETTINGSMODEL_H
#define RTT_SERIESSETTINGSMODEL_H

#include <vector>
#include <roboteam_proto/Channels.h>
#include "src/presenters/FilterPresenter.h"
#include "src/presenters/SeriesPresenter.h"

class SeriesSettingsModel {

  // Presenter
  friend class SeriesSettingsPresenter;

  // Properties
  std::vector<FilterPresenter *> filters = {};
  proto::ChannelType channel_type = proto::UNDEFINED_CHANNEL;

  // Relationships
  SeriesPresenter * parent = nullptr;

 public:
  explicit SeriesSettingsModel() = default;
};

#endif //RTT_SERIESSETTINGSMODEL_H
