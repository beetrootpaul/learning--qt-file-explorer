#include "action_quick_open_home.h"

namespace qt_file_explorer::gui {

ActionQuickOpenHome::ActionQuickOpenHome(QObject* parent,
                                         const QSharedPointer<app_state::AppState>& appState)
    : QAction(parent), appState_(appState) {
  setObjectName("ActionQuickOpenHome");

  qDebug() << "+" << this;

  setText(tr("Go to: Home"));
  // TODO: centralize shortcuts
  setShortcut(Qt::META | Qt::Key_H);

  connect(this, &QAction::triggered, this, &ActionQuickOpenHome::perform);
}

ActionQuickOpenHome::~ActionQuickOpenHome() {
  qDebug() << "~" << this;
}

void ActionQuickOpenHome::perform() {
  qDebug() << "! ActionQuickOpenHome";
  appState_->switchBrowsedDirToHome();
}

} // namespace qt_file_explorer::gui
