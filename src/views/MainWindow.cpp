#include <src/views/dialogs/WelcomeDialog.h>
#include <src/views/dialogs/NewGraphDialog.h>
#include <src/views/components/MenuBar.h>
#include <QVBoxLayout>
#include <QStringListModel>
#include <QComboBox>
#include <src/models/FilterListModel.h>
#include "MainWindow.h"

MainWindow::MainWindow() : QMainWindow() {
  auto menu = new MenuBar(this);
  this->setMenuBar(menu);


    Filter f1 = {nullptr, "hey"};
    Filter f2 = {nullptr, "hallo"};

    auto model = new FilterListModel();
    QStringList list;
    model->addFilter(f1);

    auto comboBox = new QComboBox();
    comboBox->setModel(model);
    layout()->addWidget(comboBox);

    model->addFilter(f2);

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
