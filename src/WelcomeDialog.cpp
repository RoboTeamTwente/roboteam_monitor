//
// Created by Lukas Bos on 18/10/2019.
//

#include "include/WelcomeDialog.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <include/MainWindow.h>

WelcomeDialog::WelcomeDialog(MainWindow * main_window) : QDialog(main_window) {
  connect(this, &QDialog::rejected, main_window, &MainWindow::close);

  auto dialog_horizontal_layout = new QHBoxLayout();
  this->setLayout(dialog_horizontal_layout);

  auto initial_actions_widget = new QWidget();
  auto initial_actions_layout = new QVBoxLayout();

  auto hello_world_label = new QLabel("RoboTeam Monitor!");
  initial_actions_layout->addWidget(hello_world_label);

  auto new_graph_button = new QPushButton();
  new_graph_button->setText("New graph");
  initial_actions_layout->addWidget(new_graph_button);

  connect(new_graph_button, &QPushButton::pressed, main_window, &MainWindow::open_new_graph_dialog);

  initial_actions_widget->setLayout(initial_actions_layout);
  dialog_horizontal_layout->addWidget(initial_actions_widget);
}
