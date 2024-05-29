#include <QApplication>
#include <QHBoxLayout>

#include "app_state/app_state.h"
#include "widgets/main_window.h"

// TODO: do pl/en translation switch in menu. QApplication::translate? tr(…)?

// TODO: is it possible to do a custom skin? pixel art skin?

// TODO: anything testable?

// TODO: any way to show usage of delegates?

// TODO: editable file/dir names in the listing

// TODO: persist preview if visible and its size

// TODO: icons in some buttons?

// TODO: menus with some actions same as in toolbars? QAction?

// TODO: OS-specific shortcuts for rename and undo/redo

// TODO: rename -> change the path across command history to not break undo/redo?

// TODO: remember col widths/sortings in listing

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  QApplication::setOrganizationName("Beetroot Paul");
  QApplication::setOrganizationDomain("beetrootpaul.com");
  QApplication::setApplicationName("QtFileExplorer");

  auto* appState = new qt_file_explorer::app_state::AppState();

  auto mainWindow = qt_file_explorer::widgets::MainWindow();
  mainWindow.init(
      QSharedPointer<qt_file_explorer::app_state::AppState>(appState));

  // Trigger slots listening to these signals. Thanks to that we do
  // not have to add initialization code and can rely on signals instead.
  appState->signalBrowsedDirChanged(/*originatedFromDirPicker=*/false);
  appState->signalViewTypeChanged();
  appState->signalPreviewVisibleChanged();

  mainWindow.show();

  return app.exec();
}
