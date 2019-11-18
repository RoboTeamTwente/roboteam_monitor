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
  proto::ChannelType channel_type = proto::GEOMETRY_CHANNEL;
  bool use_packet_rate = true;

  // Relationships
  SeriesPresenter * parent = nullptr;
 public:
  bool operator==(const SeriesSettingsModel &rhs) const;
  bool operator!=(const SeriesSettingsModel &rhs) const;
 public:
  explicit SeriesSettingsModel(SeriesPresenter * parent);
  explicit SeriesSettingsModel(SeriesPresenter * parent, const SeriesSettingsModel &other);
};

#endif //RTT_SERIESSETTINGSMODEL_H
