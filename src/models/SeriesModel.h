#ifndef RTT_SERIESMODEL_H
#define RTT_SERIESMODEL_H

#include "ChartModel.h"
#include <QString>
#include <roboteam_proto/Channels.h>
#include <roboteam_proto/Subscriber.h>
#include <roboteam_proto/RobotFeedback.pb.h>
#include <roboteam_proto/RobotCommand.pb.h>
#include <roboteam_proto/World.pb.h>
#include <roboteam_proto/Setting.pb.h>
#include <QtCharts/QtCharts>
#include <roboteam_utils/Timer.h>
#include <deque>

using namespace google;

class ChartPresenter;
class SeriesSettingsModel;
class SeriesSettingsPresenter;
class SeriesModel {
  friend class SeriesPresenter;
 public:
  SeriesModel(ChartPresenter * parent, json json_data);
  SeriesModel(ChartPresenter * parent, const QString & name = "Series");
  json to_json();
  ChartPresenter *get_parent() const;

 private:
  // relationships
  ChartPresenter * parent = nullptr;
  SeriesSettingsPresenter * settings_presenter = nullptr;

};

#endif //RTT_SERIESMODEL_H
