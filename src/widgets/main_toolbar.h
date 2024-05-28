#ifndef QT_FILE_EXPLORER_WIDGETS_MAIN_TOOLBAR_H
#define QT_FILE_EXPLORER_WIDGETS_MAIN_TOOLBAR_H

#include <QToolBar>

#include "../app_state/app_state.h"

namespace qt_file_explorer::widgets {

class MainToolbar : public QToolBar {

Q_OBJECT

public:
  MainToolbar();
  ~MainToolbar();

  void init(const QSharedPointer<app_state::AppState>& appState);

signals:
  void signalCollapseAllLicked();

};

} // namespace qt_file_explorer::widgets

#endif //QT_FILE_EXPLORER_WIDGETS_MAIN_TOOLBAR_H
