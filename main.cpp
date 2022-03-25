#include <QApplication>

#include "src/MainWindow/main_window.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);
  QCoreApplication::setApplicationName("Raycaster");

  MainWindow window;
  window.show();

  return QApplication::exec();
}
