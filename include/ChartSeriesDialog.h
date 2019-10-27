//
// Created by Lukas Bos on 21/10/2019.
//

#ifndef RTT_CHARTSERIESDIALOG_H
#define RTT_CHARTSERIESDIALOG_H

#include "MainWindow.h"

class ChartSeries;
class ChartSeriesDialog : public QDialog {
 private:
  QFormLayout * filters_layout;
  QWidget * create_network_settings_tab(ChartSeries * series);
 public:
  explicit ChartSeriesDialog(ChartSeries * series);

 public slots:
  void update_filters_layout(const QString & topic_name);
};

#endif //RTT_CHARTSERIESDIALOG_H
