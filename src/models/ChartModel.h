//
// Created by Lukas Bos on 12/11/2019.
//

#ifndef RTT_CHARTMODEL_H
#define RTT_CHARTMODEL_H

#include <QVariant>
#include <QAbstractListModel>
#include "ChartSeries.h"
#include "SeriesModel.h"

class ChartModel : public QObject {
  Q_OBJECT
 private:
  std::vector<SeriesModel*> series_list;
  bool dark_theme = true;

 public:
  explicit ChartModel(QObject *parent = nullptr);
  bool is_dark_theme();
  std::vector<SeriesModel*> get_series_list();

 public slots:
  void add_new_series();
  void addSeries(SeriesModel* series);
  void removeSeries(SeriesModel* series);
  void setDarkTheme(bool dark_theme);

 signals:
  void seriesChanged();
  void themeChanged();
};

#endif //RTT_CHARTMODEL_H
