#include "MainWindow.h"
#include <QApplication>

int main(int argc, char **argv) {
  QApplication qapp(argc, argv);
  MainWindow win;
  win.show();
  qapp.exec();
  
  return 0;
}
