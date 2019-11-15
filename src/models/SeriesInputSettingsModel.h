#ifndef RTT_SERIESINPUTSETTINGSMODEL_H
#define RTT_SERIESINPUTSETTINGSMODEL_H

#include <QObject>
#include <roboteam_proto/Channels.h>

class FilterModel;
class SeriesInputSettingsModel : public QObject {
 Q_OBJECT
 public:
  SeriesInputSettingsModel() = default;
  SeriesInputSettingsModel(const SeriesInputSettingsModel & other); // copy constructor

 private:
  proto::ChannelType channel_type;
 public:
  proto::ChannelType get_channel_type() const;
 private:
  std::vector<FilterModel *> filters;

 public slots:
  void add_new_filter();
  void removeFilter(FilterModel *filter_to_remove);
  const std::vector<FilterModel *> &get_filters() const;
  void update_channel(const proto::ChannelType &channel_type);

 signals:
  void filterAdded(FilterModel *filter);
  void filterRemoved(FilterModel *filter);
};

#endif //RTT_SERIESINPUTSETTINGSMODEL_H
