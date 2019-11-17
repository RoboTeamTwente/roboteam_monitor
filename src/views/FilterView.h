//
// Created by Lukas Bos on 15/11/2019.
//

#ifndef RTT_FILTERVIEW_H
#define RTT_FILTERVIEW_H

#include <QWidget>

class FilterPresenter;
class FilterView : public QWidget{
 public:
  FilterView(FilterPresenter * filterPresenter, QWidget * parent);
};

#endif //RTT_FILTERVIEW_H
