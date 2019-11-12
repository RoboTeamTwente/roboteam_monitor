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
 public:
  explicit ChartSeriesDialog(ChartSeries * series);
 public slots:
  void create_filter_view(QVBoxLayout *current_filters_layout, const Filter &filter) const;
};

#endif //RTT_CHARTSERIESDIALOG_H
