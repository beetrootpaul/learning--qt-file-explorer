#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "app_state/app_state.h"
#include "gui/main_window.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  QApplication::setOrganizationName("Beetroot Paul");
  QApplication::setOrganizationDomain("beetrootpaul.com");
  QApplication::setApplicationName("QtFileExplorer");

  auto* appState = new qt_file_explorer::app_state::AppState();

  auto mainWindow = qt_file_explorer::gui::MainWindow();
  mainWindow.init(
      QSharedPointer<qt_file_explorer::app_state::AppState>(appState));

  // Trigger slots listening to these signals. Thanks to that we do
  // not have to add initialization code and can rely on signals instead.
  appState->signalBrowsedDirChanged(/*originatedFromDirPicker=*/false);
  appState->signalBrowsedDirHistoryUpdated();
  appState->signalViewTypeChanged();
  appState->signalPreviewVisibleChanged();

  mainWindow.show();

  return app.exec();
}
