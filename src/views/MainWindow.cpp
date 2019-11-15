#include <src/views/WelcomeDialog.h>
#include <src/views/NewGraphDialog.h>
#include <src/views/components/MenuBar.h>
#include "MainWindow.h"

MainWindow::MainWindow() : QMainWindow() {
  auto menu = new MenuBar(this);
  this->setMenuBar(menu);

  open_new_graph_dialog();
}

void MainWindow::open_new_graph_dialog() {
  auto dialog = new NewGraphDialog(this);
  dialog->exec();
}

void MainWindow::open_welcome_dialog() {
  auto dialog = new WelcomeDialog(this);
  dialog->exec();
}