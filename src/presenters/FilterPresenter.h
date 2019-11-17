#ifndef RTT_FILTERPRESENTER_H
#define RTT_FILTERPRESENTER_H

#include <google/protobuf/descriptor.h>
#include <QString>

class SeriesSettingsPresenter;
class FilterModel;
class FilterPresenter {
 private:
  FilterModel * model;
 public:
  FilterPresenter(FilterModel * model);
  SeriesSettingsPresenter * getParent();
};

#endif //RTT_FILTERPRESENTER_H
