#ifndef QT_FILE_EXPLORER_MAIN_WINDOW_H
#define QT_FILE_EXPLORER_MAIN_WINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSplitter>

#include "../app_state/app_state.h"
#include "../persisted_state/with_persisted_state.h"
#include "directory_listing_icons_widget.h"
#include "directory_listing_list_widget.h"
#include "layout_toolbar.h"
#include "main_toolbar.h"

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

  MainToolbar* mainToolbar_ = nullptr;
  LayoutToolbar* layoutToolbar_ = nullptr;
  
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
