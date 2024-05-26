#ifndef QT_FILE_EXPLORER_MAIN_WINDOW_H
#define QT_FILE_EXPLORER_MAIN_WINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSplitter>

#include "../app_state/app_state.h"
#include "../with_persisted_state.h"

namespace qt_file_explorer::widgets {

class MainWindow : public QMainWindow, public WithPersistedState {

public:
  void init(const std::shared_ptr<app_state::AppState>& appState);

  void closeEvent(QCloseEvent* event) override;

private:
  QToolBar* toolbar_;
  QSplitter* splitter_;

  void savePersistedState() override;
  void loadPersistedState() override;

  void resetMainWindowLayout();
  void resetSplitterLayout();

};

} // namespace qt_file_explorer::widgets

#endif //QT_FILE_EXPLORER_MAIN_WINDOW_H
