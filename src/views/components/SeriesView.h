//
// Created by Lukas Bos on 13/11/2019.
//

#ifndef RTT_SERIESVIEW_H
#define RTT_SERIESVIEW_H

#include <QWidget>

class SeriesModel;
class SeriesView : public QWidget {
  Q_OBJECT
 private:
  SeriesModel* model;
 public:
  explicit SeriesView(SeriesModel*, QWidget * parent = nullptr);
};

#endif //RTT_SERIESVIEW_H
