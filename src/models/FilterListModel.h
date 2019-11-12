//
// Created by Lukas Bos on 12/11/2019.
//

#ifndef RTT_FILTERLISTMODEL_H
#define RTT_FILTERLISTMODEL_H

#include <iostream>
#include "ChartSeries.h"

class FilterListModel : public QAbstractListModel {
  Q_OBJECT
 private:
  QVector<Filter> filters;

 public:
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

  void addFilter(Filter filter);

  explicit FilterListModel(QObject * parent = nullptr);
};

#endif //RTT_FILTERLISTMODEL_H
