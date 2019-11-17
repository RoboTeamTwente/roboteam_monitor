#ifndef RTT_SERIESSETTINGSPRESENTER_H
#define RTT_SERIESSETTINGSPRESENTER_H

#include <QObject>
#include <roboteam_proto/Channels.h>
#include <src/models/SeriesSettingsModel.h>

class FilterPresenter;
class SeriesSettingsModel;
class SeriesSettingsPresenter : public QObject {
 Q_OBJECT
 private:
  SeriesSettingsModel * model;
  SeriesSettingsModel * snapshot = nullptr;

 public:
  SeriesSettingsPresenter(SeriesSettingsModel * model);

 public slots:
  void add_new_filter();

  void removeFilter(FilterPresenter * filter_to_remove);
  std::vector<FilterPresenter *> &get_filters();
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

#endif //RTT_SERIESSETTINGSPRESENTER_H
