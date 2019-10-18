//
// Created by Lukas Bos on 18/10/2019.
//

#ifndef RTT_WELCOMEDIALOG_H
#define RTT_WELCOMEDIALOG_H

#include <QWidget>
#include <QDialog>

class MainWindow;

class WelcomeDialog : public QDialog {
 public:
  explicit WelcomeDialog(MainWindow * main_window);
};

#endif //RTT_WELCOMEDIALOG_H
