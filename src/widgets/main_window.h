#ifndef QT_FILE_EXPLORER_MAIN_WINDOW_H
#define QT_FILE_EXPLORER_MAIN_WINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSplitter>

#include "../app_state/app_state.h"
#include "../persisted_state/with_persisted_state.h"
#include "directory_listing_icons_widget.h"
#include "directory_listing_list_widget.h"
#include "toolbars/view_toolbar_widget.h"
#include "toolbars/navigation_toolbar_widget.h"
#include "toolbars/history_toolbar_widget.h"

namespace qt_file_explorer::widgets {

class MainWindow
    : public QMainWindow, public persisted_state::WithPersistedState {

Q_OBJECT

public:
  MainWindow();
  ~MainWindow();

  void init(const QSharedPointer<app_state::AppState>& appState);

  void closeEvent(QCloseEvent* event) override;

  void savePersistedState() override;
  void loadPersistedState() override;

private:
  QSharedPointer<app_state::AppState> appState_;

  HistoryToolbarWidget* historyToolbar_ = nullptr;
  NavigationToolbarWidget* navigationToolbar_ = nullptr;
  ViewToolbarWidget* viewToolbar_ = nullptr;

  QSplitter* splitter_ = nullptr;

  QSharedPointer<DirectoryListingSharedModel> directoryListingSharedModel_;
  DirectoryListingListWidget* directoryListingList_;
  DirectoryListingIconsWidget* directoryListingIcons_;

  void resetMainWindowLayout();
  void resetSplitterLayout();

private slots:
  void slotViewTypeChanged();

};

} // namespace qt_file_explorer::widgets

#endif //QT_FILE_EXPLORER_MAIN_WINDOW_H
