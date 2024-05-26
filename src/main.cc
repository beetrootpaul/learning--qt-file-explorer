#include <iostream>

#include <QApplication>
#include <QDir>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QSettings>
#include <QSplitter>
#include <QStandardPaths>
#include <QToolBar>

#include "directory_listing_widget.h"
#include "directory_picker_widget.h"
#include "helpers.h"
#include "model.h"

using namespace qt_file_explorer;

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  helpers::examine("HOME",
                   QDir::homePath());
  helpers::examine("minecraft server",
                   QDir::homePath().append(
                       "/minecraft_server_forge_1_20_1"));
  helpers::examine("invalid path",
                   QDir::homePath().append(
                       "/does-not-exist"));
  helpers::examine("Developer",
                   QDir::homePath().append("/Developer"));
  helpers::examine("downloads",
                   QStandardPaths::standardLocations(
                       QStandardPaths::DownloadLocation));
  helpers::examine("documents",
                   QStandardPaths::standardLocations(
                       QStandardPaths::DocumentsLocation));
  helpers::examine("app local data",
                   QStandardPaths::standardLocations(
                       QStandardPaths::AppLocalDataLocation));

  auto main_window = QMainWindow();

  auto* directory_picker = new widgets::DirectoryPickerWidget();
  directory_picker->setCurrentPath(model::Model::currentPath());

  auto* directory_listing = new widgets::DirectoryListingWidget();
  directory_listing->setCurrentPath(model::Model::currentPath());

  auto* splitter = new QSplitter();
  splitter->setOrientation(Qt::Orientation::Horizontal);
  splitter->addWidget(directory_picker);
  splitter->addWidget(directory_listing);

  QSettings settings;

  settings.remove("layout");

  std::cout << "???: " << settings.contains("layout/splitter_state")
            << std::endl;

  if (settings.contains("layout/splitter_state")) {
    auto result = splitter->restoreState(
        settings.value("layout/splitter_state").toByteArray());
    std::cout << "SRestore result: " << result << std::endl;
  } else {
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 2);
  }

  QObject::connect(splitter, &QSplitter::splitterMoved,
                   [=]() {
                     std::cout << "! splitterMoved" << std::endl;
                     QSettings s;
                     s.setValue("layout/splitter_state", splitter->saveState());
                   });

  main_window.setCentralWidget(splitter);
  auto* toolbar = new QToolBar();
  toolbar->addWidget(new QPushButton("asdadsad"));
  main_window.addToolBar(toolbar);
  main_window.resize(800, 600);
  main_window.setWindowTitle("Qt File Explorer");
  main_window.show();

  return QApplication::exec();
}
