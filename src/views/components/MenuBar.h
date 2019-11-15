//
// Created by Lukas Bos on 18/10/2019.
//

#ifndef RTT_MENUBAR_H
#define RTT_MENUBAR_H

#include <QWidget>
#include <QMenuBar>

class MainWindow;
class MenuBar : public QMenuBar {
 public:
  explicit MenuBar(MainWindow * main_window);
};

#endif //RTT_MENUBAR_H
