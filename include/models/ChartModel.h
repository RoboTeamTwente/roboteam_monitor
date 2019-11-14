#ifndef RTT_CHARTMODEL_H
#define RTT_CHARTMODEL_H

#include <QObject>

class SeriesModel;
class ChartModel : public QObject {
  Q_OBJECT
 private:
  std::vector<SeriesModel *> seriesList;
  bool darkTheme = true;

 public:
  explicit ChartModel();

 public slots:
  void add_new_series();
  void delete_series(SeriesModel * series_to_delete);
  void set_theme(bool dark_theme);

  signals:
    void seriesAdded(SeriesModel * series);
    void seriesRemoved(SeriesModel * series);
    void themeChanged(bool darkTheme);
};

#endif //RTT_CHARTMODEL_H
