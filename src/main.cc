#include <iostream>

#include <QApplication>
#include <QHBoxLayout>

#include "app_state/app_state.h"
#include "widgets/main_window.h"

// TODO: non-DEBUG build?

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  QCoreApplication::setOrganizationName("Beetroot Paul");
  QCoreApplication::setOrganizationDomain("beetrootpaul.com");
  QCoreApplication::setApplicationName("QtFileExplorer");

  auto appState = std::make_shared<qt_file_explorer::app_state::AppState>();

  auto mainWindow = qt_file_explorer::widgets::MainWindow();
  mainWindow.init(appState);

  // Trigger slots listening to this signal. Thanks to that we do
  // not have to add initialization code and can rely on slots only.
  appState->changed();

  mainWindow.show();

  return app.exec();
}
