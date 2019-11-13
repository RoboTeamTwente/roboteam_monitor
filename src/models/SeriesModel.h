//
// Created by Lukas Bos on 12/11/2019.
//

#ifndef RTT_SERIESMODEL_H
#define RTT_SERIESMODEL_H

#include <QMetaType>
#include <QDebug>
#include <QAbstractItemModel>
#include <QtCharts/QtCharts>

class ChartModel;
class SeriesModel : public QObject {
  Q_OBJECT
 private:
  // relations
  ChartModel * parent;
  QXYSeries * qt_series;

 public:
  ChartModel *get_parent() const;

 public:
  explicit SeriesModel() =default;
  explicit SeriesModel(ChartModel * parent);
  ~SeriesModel();
  SeriesModel(const SeriesModel & other);

 public slots:
  void setColor(QColor color);
  QColor getColor();
  QString getName();
    void setName(QString name);
  QXYSeries * getQtSeries();

signals:
    void qtSeriesChanged();
};
Q_DECLARE_METATYPE(SeriesModel);
QDebug operator<<(QDebug dbg, const SeriesModel &series_model);

#endif //RTT_SERIESMODEL_H
