//
// Created by Lukas Bos on 18/10/2019.
//

#include <src/views/MainWindow.h>
#include "MenuBar.h"

MenuBar::MenuBar(MainWindow * main_window) : QMenuBar(main_window) {
  auto fileMenu = this->addMenu("File");

  auto new_graph_action = new QAction("new chart");
  connect(new_graph_action, &QAction::triggered, main_window, &MainWindow::open_chart_from_new_file);
  fileMenu->addAction(new_graph_action);


    auto existing_graph_action = new QAction("Open existing chart");
    connect(existing_graph_action, &QAction::triggered, main_window, &MainWindow::open_chart_from_existing_file);
    fileMenu->addAction(existing_graph_action);


    auto open_welcome_dialog_action = new QAction("Open welcome dialog");
  connect(open_welcome_dialog_action, &QAction::triggered, main_window, &MainWindow::open_welcome_dialog);
  fileMenu->addAction(open_welcome_dialog_action);
}
