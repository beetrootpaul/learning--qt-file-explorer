#include "action_next_location.h"

namespace qt_file_explorer::gui {

// TODO: enabled only if anything to redo

ActionNextLocation::ActionNextLocation(QObject* parent,
                                       const QSharedPointer<app_state::AppState>& appState)
    : QAction(parent), appState_(appState) {
  setObjectName("ActionNextLocation");

  qDebug() << "+" << this;

  setText(tr("Next location"));
  // TODO: centralize shortcuts
  setShortcut(QKeySequence::Redo);

  connect(this, &QAction::triggered, this, &ActionNextLocation::perform);
}

ActionNextLocation::~ActionNextLocation() {
  qDebug() << "~" << this;
}

void ActionNextLocation::perform() {
  qDebug() << "! ActionNextLocation";
  appState_->redoSwitchBrowsedDir();
}

} // namespace qt_file_explorer::gui
