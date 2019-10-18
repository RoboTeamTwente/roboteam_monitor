//
// Created by Lukas Bos on 18/10/2019.
//

#include <include/MainWindow.h>
#include "include/MenuBar.h"

MenuBar::MenuBar(MainWindow * main_window) : QMenuBar(main_window) {
  auto fileMenu = this->addMenu("File");

  auto new_graph_action = new QAction("New graph");
  connect(new_graph_action, &QAction::triggered, main_window, &MainWindow::open_new_graph_dialog);
  fileMenu->addAction(new_graph_action);

  auto open_welcome_dialog_action = new QAction("Open welcome dialog");
  connect(open_welcome_dialog_action, &QAction::triggered, main_window, &MainWindow::open_welcome_dialog);
  fileMenu->addAction(open_welcome_dialog_action);
}
