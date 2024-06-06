#include <QApplication>
#include <QLocale>
#include <QScopedPointer>
#include <QTranslator>

#include "app_state/app_state.h"
#include "gui/main_window.h"
#include "logging/message_handler_with_file_output.h"

int main(int argc, char* argv[]) {
#ifdef QT_DEBUG
  qt_file_explorer::logging::message_handler_with_file_output::install();
#endif // QT_DEBUG

  QApplication app(argc, argv);

  QApplication::setOrganizationName("Beetroot Paul");
  QApplication::setOrganizationDomain("beetrootpaul.com");
  QApplication::setApplicationName("QtFileExplorer");

  auto mainWindow = qt_file_explorer::gui::MainWindow();
  auto* appState = new qt_file_explorer::app_state::AppState(&mainWindow);
  mainWindow.init(appState);

  // Trigger slots listening to these signals. Thanks to that we do
  // not have to add initialization code and can rely on signals instead.
  appState->signalBrowsedDirChanged(/*originatedFromDirPicker=*/false);
  appState->signalBrowsedDirHistoryUpdated();
  appState->signalViewTypeChanged();
  appState->signalPreviewVisibleChanged();

  mainWindow.show();

  return app.exec();
}
