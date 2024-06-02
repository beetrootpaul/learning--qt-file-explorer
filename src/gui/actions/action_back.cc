#include "action_back.h"

#include "../../shortcuts.h"

namespace qt_file_explorer::gui {

ActionBack::ActionBack(QObject* parent, app_state::AppState* appState)
    : QAction(parent), appState_(appState) {
  setObjectName("ActionBack");

  qDebug() << "+" << this;

  setText(tr("Back"));
  setShortcut(Shortcuts::back());

  connect(appState_, &app_state::AppState::signalBrowsedDirHistoryUpdated, this,
          &ActionBack::slotUpdateEnabled);

  connect(this, &QAction::triggered, this, &ActionBack::perform);
}

ActionBack::~ActionBack() {
  qDebug() << "~" << this;
}

void ActionBack::slotUpdateEnabled() {
  setEnabled(appState_->canUndoSwitchBrowsedDir());
}

void ActionBack::perform() {
  qDebug() << "! ActionBack";
  appState_->undoSwitchBrowsedDir();
}

} // namespace qt_file_explorer::gui
