#include "NewGraphDialog.h"
#include "MainWindow.h"
#include <QVBoxLayout>
#include <Chart.h>

NewGraphDialog::NewGraphDialog(MainWindow * main_window) : QDialog(main_window) {
  auto new_graph_layout = new QVBoxLayout();
  this->setLayout(new_graph_layout);

  auto chart_view = new Chart();
  new_graph_layout->addWidget(chart_view);
}
