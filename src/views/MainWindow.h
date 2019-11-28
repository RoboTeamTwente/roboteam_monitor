//
// Created by Lukas Bos on 18/10/2019.
//

#ifndef RTT_MAINWINDOW_H
#define RTT_MAINWINDOW_H

#include <QMainWindow>
class QVBoxLayout;
class QWidget;
class SubscriptionManager;
class MainWindow : public QMainWindow {
 private:
  QWidget *central_widget;
  QVBoxLayout * central_layout;
  SubscriptionManager * subscription_manager;

 public:
  explicit MainWindow();
 public slots:
  void open_chart_from_new_file();
  void open_welcome_dialog();
  void open_chart_from_existing_file();
};

#endif //RTT_MAINWINDOW_H
