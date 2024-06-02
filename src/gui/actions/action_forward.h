#ifndef QT_FILE_EXPLORER_GUI_ACTIONS_ACTION_FORWARD_H
#define QT_FILE_EXPLORER_GUI_ACTIONS_ACTION_FORWARD_H

#include <QAction>
#include <QObject>

#include "../../app_state/app_state.h"

namespace qt_file_explorer::gui {

class ActionForward : public QAction {

Q_OBJECT

public:
  ActionForward(QObject* parent, app_state::AppState* appState);
  ~ActionForward();

private:
  app_state::AppState* appState_;

private slots:
  void slotUpdateEnabled();
  void perform();

};

} // namespace qt_file_explorer::gui

#endif //QT_FILE_EXPLORER_GUI_ACTIONS_ACTION_FORWARD_H
