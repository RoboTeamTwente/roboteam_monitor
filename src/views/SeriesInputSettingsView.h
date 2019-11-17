//
// Created by Lukas Bos on 15/11/2019.
//

#ifndef RTT_SERIESINPUTSETTINGSVIEW_H
#define RTT_SERIESINPUTSETTINGSVIEW_H

#include <QWidget>
#include <unordered_map>
#include <src/presenters/SeriesInputSettingsPresenter.h>

class FilterView;
class SeriesInputSettingsView : public QWidget{
  Q_OBJECT
 private:
  std::unordered_map<FilterModel *, FilterView *> filterMap;
 public:
  explicit SeriesInputSettingsView(SeriesInputSettingsPresenter * delegate, QWidget * parent = nullptr);

  void drawView(SeriesInputSettingsPresenter *delegate);
};

#endif //RTT_SERIESINPUTSETTINGSVIEW_H
