#ifndef RTT_CHARTSERIESDIALOG_H
#define RTT_CHARTSERIESDIALOG_H

#include "MainWindow.h"
#include <QDialog>

class SeriesModel;
class AddFilterDialog;
class QComboBox;
class Filter;
class ChartSeriesDialog : public QDialog {
 private:
  QString selected_topic_name;
  QVBoxLayout * network_settings_layout;
  QComboBox * channel_combo_box;
  QWidget * create_network_settings_tab(SeriesModel * series);
  QWidget * create_visualization_settings_tab(SeriesModel * series);

  AddFilterDialog * select_field_dialog;

 public:
  explicit ChartSeriesDialog(SeriesModel * series, QWidget * parent = nullptr);
 public slots:
  QWidget * create_filter_widget(QLayout * parent, Filter * filter, SeriesModel * series) const;
};

#endif //RTT_CHARTSERIESDIALOG_H
