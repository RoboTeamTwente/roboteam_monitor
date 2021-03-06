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
  SeriesSettingsModel * model = nullptr;
 public:
  SeriesSettingsModel *get_model_copy();
 private:
  SeriesSettingsModel * snapshot = nullptr;
  SeriesSettingsModel * get_internal_model();

 public:
  SeriesSettingsPresenter(SeriesSettingsModel * model);
  bool is_dirty();
  bool is_valid();
  json to_json();

 public slots:
  void add_new_filter();
  void removeFilter(FilterPresenter * filter_to_remove);
  void removeAllFilters();
  std::vector<FilterPresenter *> &get_filters();
  void update_channel(const QString & channel_str);
  void update_channel(const proto::ChannelType &channel_type);
  void set_use_packet_rate(bool use_packet_rate);
  bool use_packet_rate();
  proto::ChannelType get_channel_type();
  void createSnapShot();
  void rollBack();
  void confirm();

  void set_field_to_show(FieldDefinition * field_definition);
  FieldDefinition * get_field_to_show();

 signals:
  void filterAdded(FilterPresenter *filter);
  void filterRemoved(FilterPresenter *filter);
  void channelChanged(const proto::ChannelType &channel_type);
  void rateSettingChanged(bool use_packet_rate);
  void modelChanged();
  void finished();
  void field_to_show_changed(FieldDefinition * field_definition);
};


#endif //RTT_SERIESSETTINGSPRESENTER_H
