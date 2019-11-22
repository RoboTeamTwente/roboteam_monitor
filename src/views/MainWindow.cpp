#include <src/views/WelcomeDialog.h>
#include <src/views/components/MenuBar.h>
#include <src/models/ChartModel.h>

#include <QVBoxLayout>
#include <src/utils/Helpers.h>
#include "MainWindow.h"
#include "ChartView.h"

MainWindow::MainWindow() : QMainWindow() {
    auto menu = new MenuBar(this);
    this->setMenuBar(menu);
    central_widget = new QWidget();
    central_layout = new QVBoxLayout();
    central_widget->setLayout(central_layout);
    this->setCentralWidget(central_widget);
    open_welcome_dialog();
}

void MainWindow::open_chart_from_existing_file() {
    Helpers::clearLayout(central_layout);

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
    central_layout->addWidget(chart_view);
}

void MainWindow::open_chart_from_new_file() {
    Helpers::clearLayout(central_layout);

    auto chart_model = new ChartModel();
    auto chart_presenter = new ChartPresenter(chart_model); // this creates a new model
    auto chart_view = new ChartView(chart_presenter);
    central_layout->addWidget(chart_view);
}

void MainWindow::open_welcome_dialog() {
  auto dialog = new WelcomeDialog(this);
  dialog->exec();
}
