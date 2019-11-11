#ifndef RTT_CHARTSERIESDIALOG_H
#define RTT_CHARTSERIESDIALOG_H

#include "MainWindow.h"

class ChartSeries;
class ChartSeriesDialog : public QDialog {
 private:
  QTreeWidget * filters_tree_widget;
  QTreeWidgetItem * top_level_tree_item;
  QVBoxLayout * network_settings_layout;
  QWidget * create_network_settings_tab(ChartSeries * series);
  void add_filter_descriptor(const google::protobuf::Descriptor * descriptor, int depth, QTreeWidgetItem * parent);
 public:
  explicit ChartSeriesDialog(ChartSeries * series);

 public slots:
  void update_filters_layout(const QString & topic_name);
};

#endif //RTT_CHARTSERIESDIALOG_H
