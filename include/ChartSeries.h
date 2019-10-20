#ifndef RTT_CHARTSERIES_H
#define RTT_CHARTSERIES_H

#include <string>
#include <QtCharts/QtCharts>
#include <QWidget>

class MainWindow;
class ChartView;
class QLineEdit;
class QPushButton;
class ChartSeries : public QGroupBox {
  Q_OBJECT
 private:
  QXYSeries * qt_series;
  QPushButton * change_color_button;

 public:
  explicit ChartSeries(const QString & default_name, ChartView * chart_view);
  QXYSeries * get_qt_series();
  void set_name(const QString &name);

 public slots:
  void set_color(const QColor & color);
  void set_change_color_button_background(const QColor & color) const;
  void set_visible(bool visible);
};

#endif //RTT_CHARTSERIES_H
