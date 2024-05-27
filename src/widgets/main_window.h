#ifndef QT_FILE_EXPLORER_MAIN_WINDOW_H
#define QT_FILE_EXPLORER_MAIN_WINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSplitter>

#include "../app_state/app_state.h"
#include "../with_persisted_state.h"

namespace qt_file_explorer::widgets {

class MainWindow : public QMainWindow, public WithPersistedState {

Q_OBJECT

public:
  MainWindow();
  ~MainWindow();

  void init(QSharedPointer<app_state::AppState> appState);

  void closeEvent(QCloseEvent* event) override;

  void savePersistedState() override;
  void loadPersistedState() override;

public slots:
  void slotViewTypeChanged();

private:
  QSharedPointer<app_state::AppState> appState_;

  QToolBar* mainToolbar_;
  QToolBar* layoutToolbar_;
  QSplitter* splitter_;
  QPushButton* toggleDirListingViewTypeButton_;

  void resetMainWindowLayout();
  void resetSplitterLayout();

};

} // namespace qt_file_explorer::widgets

#endif //QT_FILE_EXPLORER_MAIN_WINDOW_H
