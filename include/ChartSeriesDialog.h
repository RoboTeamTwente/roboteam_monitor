#ifndef RTT_CHARTSERIESDIALOG_H
#define RTT_CHARTSERIESDIALOG_H

#include "MainWindow.h"

class ChartSeries;
class ChartSeriesDialog : public QDialog {
 private:
  QString selected_topic_name;
  QVBoxLayout * network_settings_layout;
  QComboBox * channel_combo_box;
  QWidget * create_network_settings_tab(ChartSeries * series);
  QWidget * create_visualization_settings_tab(ChartSeries * series);

 public:
  explicit ChartSeriesDialog(ChartSeries * series);
 public slots:
  QWidget * create_filter_widget(QLayout * parent, const Filter &filter) const;
};

#endif //RTT_CHARTSERIESDIALOG_H
