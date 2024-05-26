#include "main_window.h"

#include <iostream>

#include <QSettings>

namespace qt_file_explorer {

MainWindow::MainWindow() {
  readSettings();
}

void MainWindow::closeEvent(QCloseEvent* event) {
  writeSettings();
  QMainWindow::closeEvent(event);
}

void MainWindow::readSettings() {
  std::cout << "READ SETTINGS" << std::endl;

  QSettings settings;

  const auto size = settings.value("layout/main_window/size").toSize();
  if (size.isEmpty()) {
    std::cout << "! empty size !" << std::endl;
    resize(800, 600);
  } else {
    std::cout << "~ restore size ~" << std::endl;
    resize(size);
  }

  const auto pos = settings.value("layout/main_window/pos").toPoint();
  if (pos.isNull()) {
    std::cout << "! empty pos !" << std::endl;
    // TODO: make it centered
    move(10, 10);
  } else {
    std::cout << "~ restore pos ~" << std::endl;
    // TODO: make it always visible even if screen size decreases
    move(pos);
  }

  const auto state = settings.value("layout/main_window/state",
                                    QByteArray()).toByteArray();
  if (state.isEmpty()) {
    std::cout << "! empty state !" << std::endl;
  } else {
    std::cout << "~ restore state ~" << std::endl;
    restoreState(state);
  }
}

void MainWindow::writeSettings() {
  std::cout << "WRITE SETTINGS" << std::endl;

  QSettings settings;
  settings.setValue("layout/main_window/size", size());
  settings.setValue("layout/main_window/pos", pos());
  settings.setValue("layout/main_window/state", saveState());
}

} // namespace qt_file_explorer
