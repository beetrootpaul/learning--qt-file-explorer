#include "action_forward.h"

#include "../../shortcuts.h"

namespace qt_file_explorer::gui {

ActionForward::ActionForward(QObject* parent,
                             const QSharedPointer<app_state::AppState>& appState)
    : QAction(parent), appState_(appState) {
  setObjectName("ActionForward");

  qDebug() << "+" << this;

  setText(tr("Forward"));
  setShortcut(Shortcuts::forward());

  connect(appState_.data(),
          &app_state::AppState::signalBrowsedDirHistoryUpdated, this,
          &ActionForward::slotUpdateEnabled);

  connect(this, &QAction::triggered, this, &ActionForward::perform);
}

// TODO: README: describe cross-OS shortcuts based on https://doc.qt.io/qt-6/qkeysequence.html#standard-shortcuts

ActionForward::~ActionForward() {
  qDebug() << "~" << this;
}

void ActionForward::slotUpdateEnabled() {
  setEnabled(appState_->canRedoSwitchBrowsedDir());
}

void ActionForward::perform() {
  qDebug() << "! ActionForward";
  appState_->redoSwitchBrowsedDir();
}

} // namespace qt_file_explorer::gui
