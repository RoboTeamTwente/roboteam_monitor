//
// Created by Lukas Bos on 15/11/2019.
//

#ifndef RTT_FILTERVIEW_H
#define RTT_FILTERVIEW_H

#include <QWidget>
#include <src/presenters/SeriesInputSettingsPresenter.h>
#include "src/models/FilterModel.h"

class SeriesInputSettingsPresenter;
class FilterView : public QWidget{
 private:
  SeriesInputSettingsPresenter * input_settings_delegate;
  FilterModel * filterModel;

 public:
  FilterView(FilterModel * filterModel, SeriesInputSettingsPresenter * series_input_settings_delegate, QWidget * parent);
};

#endif //RTT_FILTERVIEW_H
