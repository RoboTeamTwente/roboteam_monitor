#ifndef RTT_SERIESSETTINGSMODEL_H
#define RTT_SERIESSETTINGSMODEL_H

#include <vector>
#include <roboteam_proto/Channels.h>
#include <roboteam_utils/json.hpp>
#include "FieldDefinition.h"

using json = nlohmann::json;

class FilterPresenter;
class SeriesPresenter;
class SeriesSettingsPresenter;
class SeriesSettingsModel {

  // Presenter
  friend class SeriesSettingsPresenter;

  // Properties
  std::vector<FilterPresenter *> filters = {};
  proto::ChannelType channel_type = proto::GEOMETRY_CHANNEL;
  bool use_packet_rate = true;
  FieldDefinition * field_to_show = nullptr;

  // Relationships
  SeriesPresenter * parent = nullptr;
 public:
  bool operator==(const SeriesSettingsModel &rhs) const;
  bool operator!=(const SeriesSettingsModel &rhs) const;
  bool is_valid();
  json to_json();
 public:
  explicit SeriesSettingsModel(SeriesPresenter * parent);
  explicit SeriesSettingsModel(SeriesPresenter * parent, json data);
  explicit SeriesSettingsModel(const SeriesSettingsModel &other, SeriesSettingsPresenter * presenter);
};

#endif //RTT_SERIESSETTINGSMODEL_H
