#include <QApplication>
#include <QStyleFactory>
#include "src/views/components/MenuBar.h"
#include "src/views/MainWindow.h"
#include "../../roboteam_ai/include/roboteam_ai/control/RobotCommand.h"
#include <thread>
#include <roboteam_utils/Timer.h>
#include <roboteam_proto/Publisher.h>

void setDarkTheme() {
  qApp->setStyle(QStyleFactory::create("Fusion"));
  QPalette darkPalette;
  darkPalette.setColor(QPalette::Window, QColor(53,53,53));
  darkPalette.setColor(QPalette::WindowText, Qt::white);
  darkPalette.setColor(QPalette::Base, QColor(25,25,25));
  darkPalette.setColor(QPalette::AlternateBase, QColor(53,53,53));
  darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
  darkPalette.setColor(QPalette::ToolTipText, Qt::white);
  darkPalette.setColor(QPalette::Text, Qt::white);
  darkPalette.setColor(QPalette::Button, QColor(53,53,53));
  darkPalette.setColor(QPalette::ButtonText, Qt::white);
  darkPalette.setColor(QPalette::BrightText, Qt::red);
  darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
  darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
  darkPalette.setColor(QPalette::HighlightedText, Qt::black);
  qApp->setPalette(darkPalette);
  qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
}


void fakeRobotCommands() {
    roboteam_utils::Timer t;
    auto publisher = new proto::Publisher<proto::RobotCommand>(proto::ChannelType::ROBOT_COMMANDS_PRIMARY_CHANNEL);

    int id = 0;
    float w = 50.0;
    t.loop([&]() {
        auto cmd = new proto::RobotCommand;

      if (w > 100) {
          w = 50;

      } else {
          w+=0.1;
      }


        cmd->set_id(id);
        if (id == 1) {
            id = 0;
            cmd->set_w(100-w);
        }
        else if (id == 0) {
            id = 1;
            cmd->set_w(w);
        }
        cmd->mutable_vel()->set_x(10);
        cmd->mutable_vel()->set_y(20);

        publisher->send(*cmd);
    }, 100);
}

int main(int argc, char** argv) {
  QApplication a(argc, argv);
  setDarkTheme();

  std::thread thread(fakeRobotCommands);
  MainWindow window;
  window.setWindowState(Qt::WindowMaximized);
  window.show();

  return a.exec();
}

