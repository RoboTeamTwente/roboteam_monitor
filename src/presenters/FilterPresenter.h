#ifndef RTT_FILTERPRESENTER_H
#define RTT_FILTERPRESENTER_H

#include <google/protobuf/descriptor.h>
#include <QString>

class SeriesInputSettingsPresenter;
class FilterModel;
class FilterPresenter {
 private:
  FilterModel * model;
 public:
  FilterPresenter(FilterModel * model);
  SeriesInputSettingsPresenter * getParent();
};

#endif //RTT_FILTERPRESENTER_H
