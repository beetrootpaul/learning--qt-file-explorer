#include <QApplication>
#include <QDir>
#include <QHBoxLayout>
#include <QMainWindow>
#include <QPushButton>
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

  auto* container = new QWidget();
  auto* layout = new QHBoxLayout(container);
  layout->addWidget(directory_picker);
  layout->addWidget(directory_listing);

  main_window.setCentralWidget(container);
  auto* toolbar = new QToolBar();
  toolbar->addWidget(new QPushButton("asdadsad"));
  main_window.addToolBar(toolbar);
  main_window.resize(800, 600);
  main_window.setWindowTitle("Qt File Explorer");
  main_window.show();

  return QApplication::exec();
}
