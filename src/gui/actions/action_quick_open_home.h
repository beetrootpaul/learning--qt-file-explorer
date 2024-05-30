#ifndef QT_FILE_EXPLORER_GUI_ACTIONS_ACTION_QUICK_OPEN_HOME_H
#define QT_FILE_EXPLORER_GUI_ACTIONS_ACTION_QUICK_OPEN_HOME_H

#include <QAction>
#include <QObject>

#include "../../app_state/app_state.h"

namespace qt_file_explorer::gui {

class ActionQuickOpenHome : public QAction {

Q_OBJECT

public:
  ActionQuickOpenHome(QObject* parent,
                      const QSharedPointer<app_state::AppState>& appState);
  ~ActionQuickOpenHome();

private:
  QSharedPointer<app_state::AppState> appState_;

private slots:
  void perform();

};

} // namespace qt_file_explorer::gui

#endif //QT_FILE_EXPLORER_GUI_ACTIONS_ACTION_QUICK_OPEN_HOME_H
