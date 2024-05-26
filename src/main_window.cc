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
  const auto geometry = settings.value("layout/main_window/geometry",
                                       QByteArray()).toByteArray();
  if (geometry.isEmpty()) {
    std::cout << "! empty geometry !" << std::endl;
    resize(800, 600);
  } else {
    std::cout << "~ restore geometry ~" << std::endl;
    restoreGeometry(geometry);
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
  settings.setValue("layout/main_window/geometry", saveGeometry());
  settings.setValue("layout/main_window/state", saveState());
}

} // namespace qt_file_explorer
