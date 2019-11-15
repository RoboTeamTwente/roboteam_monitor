//
// Created by Lukas Bos on 15/11/2019.
//

#ifndef RTT_SERIESINPUTSETTINGSVIEW_H
#define RTT_SERIESINPUTSETTINGSVIEW_H

#include <QWidget>
#include <unordered_map>
#include <src/models/SeriesInputSettingsModel.h>

class FilterView;
class SeriesInputSettingsView : public QWidget{
 private:
  std::unordered_map<FilterModel *, FilterView *> filterMap;
 public:
  SeriesInputSettingsView(SeriesInputSettingsModel * model, QWidget * parent = nullptr);
};

#endif //RTT_SERIESINPUTSETTINGSVIEW_H
