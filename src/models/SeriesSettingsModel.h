#ifndef RTT_SERIESSETTINGSMODEL_H
#define RTT_SERIESSETTINGSMODEL_H

#include <vector>
#include <roboteam_proto/Channels.h>
#include "src/presenters/SeriesPresenter.h"

class FilterPresenter;
class SeriesSettingsModel {

  // Presenter
  friend class SeriesSettingsPresenter;

  // Properties
  std::vector<FilterPresenter *> filters = {};
  proto::ChannelType channel_type = proto::UNDEFINED_CHANNEL;
  bool show_packet_rate = true;
  bool show_custom_field = false;

  // Relationships
  SeriesPresenter * parent = nullptr;
 public:
  bool operator==(const SeriesSettingsModel &rhs) const;
  bool operator!=(const SeriesSettingsModel &rhs) const;
 public:
  explicit SeriesSettingsModel() = default;
  explicit SeriesSettingsModel(const SeriesSettingsModel &other);
};

#endif //RTT_SERIESSETTINGSMODEL_H
