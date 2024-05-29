#ifndef QT_FILE_EXPLORER_WIDGETS_TOOLBARS_HISTORY_TOOLBAR_H
#define QT_FILE_EXPLORER_WIDGETS_TOOLBARS_HISTORY_TOOLBAR_H

#include <QToolBar>

#include "../../app_state/app_state.h"

namespace qt_file_explorer::widgets {

class HistoryToolbarWidget : public QToolBar {

Q_OBJECT

public:
  HistoryToolbarWidget();
  ~HistoryToolbarWidget();

  void init(const QSharedPointer<app_state::AppState>& appState);

};

} // namespace qt_file_explorer::widgets

#endif //QT_FILE_EXPLORER_WIDGETS_TOOLBARS_HISTORY_TOOLBAR_H
