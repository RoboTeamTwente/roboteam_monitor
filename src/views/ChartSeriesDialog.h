#ifndef RTT_CHARTSERIESDIALOG_H
#define RTT_CHARTSERIESDIALOG_H

#include "MainWindow.h"
#include <QDialog>
#include <QHBoxLayout>

class SeriesPresenter;
class AddFilterDialog;
class QComboBox;
class FilterPresenter;
class FilterView;
class ChartSeriesDialog : public QDialog {
 private:
  QString selected_topic_name;
  QVBoxLayout * network_settings_layout;
  QComboBox * channel_combo_box;
  // QWidget * create_visualization_settings_tab(SeriesPresenter * series);

  AddFilterDialog * select_field_dialog;

 public:
  explicit ChartSeriesDialog(SeriesPresenter * series_presenter, QWidget * parent = nullptr);
  // QHBoxLayout *create_buttons_layout(SeriesPresenter *series);
};

#endif //RTT_CHARTSERIESDIALOG_H
