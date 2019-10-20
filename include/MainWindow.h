//
// Created by Lukas Bos on 18/10/2019.
//

#ifndef RTT_MAINWINDOW_H
#define RTT_MAINWINDOW_H

#include <QMainWindow>
class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  explicit MainWindow();

 public slots:
  void open_new_graph_dialog();
  void open_welcome_dialog();
};

#endif //RTT_MAINWINDOW_H
