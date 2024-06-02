#include "action_go_to_home.h"

#include "../../shortcuts.h"

namespace qt_file_explorer::gui {

ActionGoToHome::ActionGoToHome(QObject* parent, app_state::AppState* appState)
    : QAction(parent), appState_(appState) {
  setObjectName("ActionGoToHome");

  qDebug() << "+" << this;

  setText(tr("Go to: Home"));
  setShortcut(Shortcuts::goToHome());

  connect(this, &QAction::triggered, this, &ActionGoToHome::perform);
}

ActionGoToHome::~ActionGoToHome() {
  qDebug() << "~" << this;
}

void ActionGoToHome::perform() {
  qDebug() << "! ActionGoToHome";
  appState_->switchBrowsedDirToHome();
}

} // namespace qt_file_explorer::gui
