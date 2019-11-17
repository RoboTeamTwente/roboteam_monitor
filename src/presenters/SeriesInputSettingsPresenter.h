#ifndef RTT_SERIESINPUTSETTINGSPRESENTER_H
#define RTT_SERIESINPUTSETTINGSPRESENTER_H

#include <QObject>
#include <roboteam_proto/Channels.h>
#include <src/models/SeriesInputSettingsModel.h>

class FilterPresenter;
class SeriesInputSettingsModel;
class SeriesInputSettingsPresenter : public QObject {
 Q_OBJECT
 private:
  SeriesInputSettingsModel * model;
  SeriesInputSettingsModel * snapshot = nullptr;

 public:
  SeriesInputSettingsPresenter(SeriesInputSettingsModel * model);

 public slots:
  void add_new_filter();
  void removeFilter(FilterModel * filter_to_remove);
  const std::vector<FilterModel> &get_filters() const;
  void update_channel(const proto::ChannelType &channel_type);
  proto::ChannelType get_channel_type() const;
  void createSnapShot();
  void rollBack();
  void confirm();

 signals:
  void filterAdded(FilterPresenter *filter);
  void filterRemoved(FilterPresenter *filter);
  void modelChanged();
  void finished();
};

#endif //RTT_SERIESINPUTSETTINGSPRESENTER_H
