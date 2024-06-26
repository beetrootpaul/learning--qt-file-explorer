#ifndef QT_FILE_EXPLORER_GUI_ACTIONS_ACTION_BACK_H
#define QT_FILE_EXPLORER_GUI_ACTIONS_ACTION_BACK_H

#include <QAction>
#include <QObject>

#include "../../app_state/app_state.h"

namespace qt_file_explorer::gui {

class ActionBack : public QAction {

Q_OBJECT

public:
  ActionBack(QObject* parent, app_state::AppState* appState);
  ~ActionBack();

private:
  app_state::AppState* appState_;

private slots:
  void slotUpdateEnabled();
  void perform();

};

} // namespace qt_file_explorer::gui

#endif //QT_FILE_EXPLORER_GUI_ACTIONS_ACTION_BACK_H
