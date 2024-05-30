#ifndef QT_FILE_EXPLORER_MAIN_WINDOW_H
#define QT_FILE_EXPLORER_MAIN_WINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSplitter>

#include "../app_state/app_state.h"
#include "../persisted_state/with_persisted_state.h"
#include "dir_listing/dir_listing_icons_widget.h"
#include "dir_listing/dir_listing_list_widget.h"
#include "dir_picker/dir_picker_widget.h"
#include "preview/preview_dock_widget.h"
#include "toolbar.h"

namespace qt_file_explorer::gui {

class MainWindow
    : public QMainWindow, public persisted_state::WithPersistedState {

Q_OBJECT

public:
  MainWindow();
  ~MainWindow();

  void init(const QSharedPointer<app_state::AppState>& appState);

  void closeEvent(QCloseEvent* event) override;

  void resetLayout();

  void savePersistedState() override;
  void loadPersistedState() override;

private:
  QSharedPointer<app_state::AppState> appState_;

  Toolbar* toolbarNavigation_ = nullptr;
  Toolbar* toolbarView_ = nullptr;

  QSplitter* splitter_ = nullptr;

  QSharedPointer<DirListingSharedModel> dirListingSharedModel_;
  DirPickerWidget* dirPicker_;
  DirListingListWidget* dirListingList_;
  DirListingIconsWidget* dirListingIcons_;
  PreviewDockWidget* previewDock_;

  QAction* actionPrevLocation_;
  QAction* actionNextLocation_;
  QAction* actionCollapseAll_;
  QAction* actionQuickOpenHome_;
  QAction* actionQuickOpenDownloads_;
  QAction* actionToggleDirListingViewType_;
  QAction* actionTogglePreview_;
  QAction* actionResetLayout_;

  void initSplitter();
  void initPreview();
  void initToolbars();
  void initMenus();

  void resetMainWindowLayout();
  void resetSplitterLayout();

private slots:
  void slotViewTypeChanged();
  void slotPreviewVisibleChanged();

};

} // namespace qt_file_explorer::gui

#endif //QT_FILE_EXPLORER_MAIN_WINDOW_H
