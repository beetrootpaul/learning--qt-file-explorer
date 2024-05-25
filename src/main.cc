#include <iostream>

#include <QApplication>
#include <QDir>
#include <QDockWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QStandardPaths>
#include <QToolBar>

#include "helpers.h"
#include "directory_picker/directory_picker_widget.h"

// TODO: extract most to a new class QtFileExplorer

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  qt_file_explorer::examine("HOME",
                            QDir::homePath());
  qt_file_explorer::examine("minecraft server",
                            QDir::homePath().append(
                                "/minecraft_server_forge_1_20_1"));
  qt_file_explorer::examine("invalid path",
                            QDir::homePath().append("/does-not-exist"));
  qt_file_explorer::examine("Developer",
                            QDir::homePath().append("/Developer"));
  qt_file_explorer::examine("downloads",
                            QStandardPaths::standardLocations(
                                QStandardPaths::DownloadLocation));
  qt_file_explorer::examine("documents",
                            QStandardPaths::standardLocations(
                                QStandardPaths::DocumentsLocation));
  qt_file_explorer::examine("app local data",
                            QStandardPaths::standardLocations(
                                QStandardPaths::AppLocalDataLocation));

  auto* button = new QPushButton("btn1");

  auto* toolbar = new QToolBar();
  toolbar->setFloatable(false);
  toolbar->setMovable(false);
  toolbar->addWidget(button);

  auto main_window = QMainWindow();
  main_window.resize(800, 600);

  auto* directory_picker = new qt_file_explorer::DirectoryPickerWidget();

  main_window.setCentralWidget(directory_picker);

  QStringList download_locations =
      QStandardPaths::standardLocations(QStandardPaths::DownloadLocation);
  if (download_locations.count() > 0) {
    directory_picker->setCurrentPath(download_locations.first());
  }

  main_window.addToolBar(toolbar);

  main_window.setWindowTitle(
      QApplication::translate("window", "Qt File Explorer"));
  main_window.show();

  return QApplication::exec();
}
