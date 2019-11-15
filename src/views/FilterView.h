//
// Created by Lukas Bos on 15/11/2019.
//

#ifndef RTT_FILTERVIEW_H
#define RTT_FILTERVIEW_H

#include <QWidget>
#include <src/models/SeriesInputSettingsModel.h>
#include "src/models/FilterModel.h"

class FilterView : public QWidget{
 private:
  SeriesInputSettingsModel * inputSettingsModel;
  FilterModel * filterModel;

 public:
  FilterView(FilterModel * filterModel, SeriesInputSettingsModel * inputSettingsModel, QWidget * parent);
};

#endif //RTT_FILTERVIEW_H
