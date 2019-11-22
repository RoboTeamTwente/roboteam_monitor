#ifndef RTT_SERIESSETTINGSDIALOG_H
#define RTT_SERIESSETTINGSDIALOG_H

#include "MainWindow.h"
#include <QDialog>
#include <unordered_map>

class SeriesSettingsPresenter;
class FilterPresenter;
class FilterView;
class SeriesSettingsDialog : public QDialog {
  Q_OBJECT
 private:
  std::unordered_map<FilterPresenter *, FilterView *> filterMap;
  SeriesSettingsPresenter * presenter;

 public:
  explicit SeriesSettingsDialog(SeriesSettingsPresenter * presenter, QWidget * parent = nullptr);
  int exec();

  signals:
    void user_event_dirty(bool dirty);

};

#endif //RTT_SERIESSETTINGSDIALOG_H
