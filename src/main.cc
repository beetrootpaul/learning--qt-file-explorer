#include <iostream>

#include <QApplication>
#include <QHBoxLayout>

#include "app_state/app_state.h"
#include "widgets/main_window.h"

// TODO: non-DEBUG build?

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  QApplication::setOrganizationName("Beetroot Paul");
  QApplication::setOrganizationDomain("beetrootpaul.com");
  QApplication::setApplicationName("QtFileExplorer");

  qt_file_explorer::app_state::AppState appState;

  auto mainWindow = qt_file_explorer::widgets::MainWindow();
  mainWindow.init(&appState);

  // Trigger slots listening to this signal. Thanks to that we do
  // not have to add initialization code and can rely on slots only.
  appState.changed();

  mainWindow.show();

  return app.exec();
}
