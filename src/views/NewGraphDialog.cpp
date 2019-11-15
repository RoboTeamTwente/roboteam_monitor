#include "NewGraphDialog.h"
#include "MainWindow.h"
#include <QVBoxLayout>
#include <src/models/ChartModel.h>
#include <src/views/ChartView.h>

NewGraphDialog::NewGraphDialog(MainWindow * main_window) : QDialog(main_window) {
  auto new_graph_layout = new QVBoxLayout();
  this->setLayout(new_graph_layout);

  auto chart_model = new ChartModel();
  auto chart_view = new ChartView(chart_model);
  new_graph_layout->addWidget(chart_view);
}
