#ifndef QT_FILE_EXPLORER_GUI_ACTIONS_ACTION_TOGGLE_PREVIEW_H
#define QT_FILE_EXPLORER_GUI_ACTIONS_ACTION_TOGGLE_PREVIEW_H

#include <QAction>
#include <QObject>

#include "../../app_state/app_state.h"

namespace qt_file_explorer::gui {

class ActionTogglePreview : public QAction {

Q_OBJECT

public:
  ActionTogglePreview(QObject* parent, app_state::AppState* appState);
  ~ActionTogglePreview();

private:
  app_state::AppState* appState_;

private slots:
  void perform();

};

} // namespace qt_file_explorer::gui

#endif //QT_FILE_EXPLORER_GUI_ACTIONS_ACTION_TOGGLE_PREVIEW_H
