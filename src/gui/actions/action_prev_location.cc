#include "action_prev_location.h"

namespace qt_file_explorer::gui {

// TODO: do not add same location switches to history OR do not react to such clicks at all

// TODO: enabled only if anything to undo

ActionPrevLocation::ActionPrevLocation(QObject* parent,
                                       const QSharedPointer<app_state::AppState>& appState)
    : QAction(parent), appState_(appState) {
  setObjectName("ActionPrevLocation");

  qDebug() << "+" << this;

  setText(tr("Back"));
  // TODO: centralize shortcuts
  setShortcut(QKeySequence::Back);

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
