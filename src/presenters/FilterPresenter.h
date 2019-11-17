#ifndef RTT_FILTERPRESENTER_H
#define RTT_FILTERPRESENTER_H

#include <google/protobuf/descriptor.h>
#include <QString>
#include <src/models/FilterModel.h>

class FilterPresenter {
 private:
  FilterModel * model;
 public:
  FilterPresenter(FilterModel * model);
};

#endif //RTT_FILTERPRESENTER_H
