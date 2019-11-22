#include <src/views/WelcomeDialog.h>
#include <src/views/NewGraphDialog.h>
#include <src/views/components/MenuBar.h>
#include <src/models/ChartModel.h>

#include <QVBoxLayout>
#include "MainWindow.h"
#include "ChartView.h"

MainWindow::MainWindow() : QMainWindow() {
    auto menu = new MenuBar(this);
    this->setMenuBar(menu);


    // instantly ask to load a file
    json chart_json;
    auto file_name = QFileDialog::getOpenFileName(this, tr("Open rtt file"), "", tr("(*.rtt)"));
    QFile file(file_name);
    if (file.open(QIODevice::ReadOnly)) {
        QString data_from_file;
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            data_from_file.append(line);
        }
        chart_json = json::parse(data_from_file.toStdString());
    }

    auto chart_presenter = new ChartPresenter(chart_json); // this creates a new model
    auto chart_view = new ChartView(chart_presenter);
    this->setCentralWidget(chart_view);


}

void MainWindow::open_new_graph_dialog() {
  auto dialog = new NewGraphDialog(this);
  dialog->exec();
}

void MainWindow::open_welcome_dialog() {
  auto dialog = new WelcomeDialog(this);
  dialog->exec();
}
