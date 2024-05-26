#include <iostream>

#include <QApplication>
#include <QDir>
#include <QHBoxLayout>
#include <QStandardPaths>

#include "helpers.h"
#include "main_window.h"
#include "model.h"

// TODO: group some files into dirs

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  QCoreApplication::setOrganizationName("Beetroot Paul");
  QCoreApplication::setOrganizationDomain("beetrootpaul.com");
  QCoreApplication::setApplicationName("QtFileExplorer");

  qt_file_explorer::helpers::examine("HOME",
                                     QDir::homePath());
  qt_file_explorer::helpers::examine("minecraft server",
                                     QDir::homePath().append(
                                         "/minecraft_server_forge_1_20_1"));
  qt_file_explorer::helpers::examine("invalid path",
                                     QDir::homePath().append(
                                         "/does-not-exist"));
  qt_file_explorer::helpers::examine("Developer",
                                     QDir::homePath().append("/Developer"));
  qt_file_explorer::helpers::examine("downloads",
                                     QStandardPaths::standardLocations(
                                         QStandardPaths::DownloadLocation));
  qt_file_explorer::helpers::examine("documents",
                                     QStandardPaths::standardLocations(
                                         QStandardPaths::DocumentsLocation));
  qt_file_explorer::helpers::examine("app local data",
                                     QStandardPaths::standardLocations(
                                         QStandardPaths::AppLocalDataLocation));

  auto main_window = qt_file_explorer::widgets::MainWindow();

  main_window.setModel(new qt_file_explorer::model::Model());

//  QSettings settings;

//  settings.remove("layout");

//  std::cout << "???: " << settings.contains("layout/splitter_state")
//            << std::endl;

//  if (settings.contains("layout/splitter_state")) {
//    auto result = splitter->restoreState(
//        settings.value("layout/splitter_state").toByteArray());
//    std::cout << "SRestore result: " << result << std::endl;
//  } else {
//    splitter->setStretchFactor(0, 1);
//    splitter->setStretchFactor(1, 2);
//  }

//  QObject::connect(splitter, &QSplitter::splitterMoved,
//                   [=]() {
//                     std::cout << "! splitterMoved" << std::endl;
  // TODO: move it to closeEvent
//                     QSettings s;
//                     s.setValue("layout/splitter_state", splitter->saveState());
//                   });

  main_window.show();

  return QApplication::exec();
}
