#include "action_prev_location.h"

namespace qt_file_explorer::gui {

// TODO: enabled only if anything to undo

ActionPrevLocation::ActionPrevLocation(QObject* parent,
                                       const QSharedPointer<app_state::AppState>& appState)
    : QAction(parent), appState_(appState) {
  setObjectName("ActionPrevLocation");

  qDebug() << "+" << this;

  setText(tr("Previous location"));
  // TODO: centralize shortcuts
  setShortcut(QKeySequence::Undo);

  connect(this, &QAction::triggered, this, &ActionPrevLocation::perform);
}

ActionPrevLocation::~ActionPrevLocation() {
  qDebug() << "~" << this;
}

void ActionPrevLocation::perform() {
  qDebug() << "! ActionPrevLocation";
  appState_->undoSwitchBrowsedDir();
}

} // namespace qt_file_explorer::gui
