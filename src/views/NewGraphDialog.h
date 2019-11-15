#ifndef RTT_NEWGRAPHDIALOG_H
#define RTT_NEWGRAPHDIALOG_H

#include <QWidget>
#include <QDialog>

class MainWindow;
class NewGraphDialog : public QDialog {
  public:
 explicit NewGraphDialog(MainWindow * main_window);
};

#endif //RTT_NEWGRAPHDIALOG_H
