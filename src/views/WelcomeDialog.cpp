#include "WelcomeDialog.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "MainWindow.h"

WelcomeDialog::WelcomeDialog(MainWindow * main_window) : QDialog(main_window) {

  auto dialog_horizontal_layout = new QHBoxLayout();
  this->setLayout(dialog_horizontal_layout);

  auto initial_actions_widget = new QWidget();
  auto initial_actions_layout = new QVBoxLayout();

  auto hello_world_label = new QLabel("RoboTeam Monitor!");
    hello_world_label->setStyleSheet("color: #cc0000; font-weight: 600; font-size: 28px;");
  initial_actions_layout->addWidget(hello_world_label);

  auto new_graph_button = new QPushButton();
  new_graph_button->setText("New graph");
  initial_actions_layout->addWidget(new_graph_button);


    auto existing_graph_button = new QPushButton();
    existing_graph_button->setText("Open existing graph");
    initial_actions_layout->addWidget(existing_graph_button);


  initial_actions_widget->setLayout(initial_actions_layout);
  dialog_horizontal_layout->addWidget(initial_actions_widget);


connect(existing_graph_button, &QPushButton::pressed, main_window, &MainWindow::open_chart_from_existing_file);
    connect(existing_graph_button, &QPushButton::pressed, this, &QDialog::close);

connect(new_graph_button, &QPushButton::pressed, main_window, &MainWindow::open_chart_from_new_file);
    connect(new_graph_button, &QPushButton::pressed, this, &QDialog::close);

connect(this, &QDialog::rejected, main_window, &MainWindow::close);

}
