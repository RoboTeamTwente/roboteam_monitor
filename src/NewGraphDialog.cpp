#include "include/NewGraphDialog.h"
#include "include/MainWindow.h"
#include <QVBoxLayout>
#include <include/ChartView.h>

NewGraphDialog::NewGraphDialog(MainWindow * main_window) : QDialog(main_window) {
  auto new_graph_layout = new QVBoxLayout();
  this->setLayout(new_graph_layout);

  auto chart_view = new ChartView();
  new_graph_layout->addWidget(chart_view);
}
