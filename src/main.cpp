//
// Created by Lukas Bos on 18/10/2019.
//

#include <QApplication>
#include <memory>
#include "include/MenuBar.h"
#include "include/MainWindow.h"

int main(int argc, char** argv) {
  QApplication a(argc, argv);
  MainWindow window;
  window.setWindowState(Qt::WindowMaximized);
  window.show();
  return a.exec();
}