//
// Created by Lukas Bos on 15/11/2019.
//

#ifndef RTT_SERIESINPUTSETTINGSVIEW_H
#define RTT_SERIESINPUTSETTINGSVIEW_H

#include <QWidget>
#include <unordered_map>
#include <src/presenters/SeriesSettingsPresenter.h>

class FilterView;
class SeriesInputSettingsView : public QWidget{
  Q_OBJECT
 private:
  std::unordered_map<FilterPresenter *, FilterView *> filterMap;
 public:
  explicit SeriesInputSettingsView(SeriesSettingsPresenter * presenter, QWidget * parent = nullptr);
};

#endif //RTT_SERIESINPUTSETTINGSVIEW_H
