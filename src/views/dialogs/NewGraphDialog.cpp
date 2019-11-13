#include "NewGraphDialog.h"
#include "src/views/MainWindow.h"
#include <QVBoxLayout>
#include <src/views/components/ChartView.h>

NewGraphDialog::NewGraphDialog(MainWindow * main_window) : QDialog(main_window) {
  auto new_graph_layout = new QVBoxLayout();
  this->setLayout(new_graph_layout);

  auto model = new ChartModel();
  auto chart_view = new ChartView(model);
  new_graph_layout->addWidget(chart_view);
}
