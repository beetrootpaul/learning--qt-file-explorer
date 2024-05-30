#include "action_back.h"

#include "../../shortcuts.h"

namespace qt_file_explorer::gui {

// TODO: do not add same location switches to history OR do not react to such clicks at all

// TODO: enabled only if anything to undo

ActionBack::ActionBack(QObject* parent,
                       const QSharedPointer<app_state::AppState>& appState)
    : QAction(parent), appState_(appState) {
  setObjectName("ActionBack");

  qDebug() << "+" << this;

  setText(tr("Back"));
  setShortcut(Shortcuts::back());

  connect(this, &QAction::triggered, this, &ActionBack::perform);
}

ActionBack::~ActionBack() {
  qDebug() << "~" << this;
}

void ActionBack::perform() {
  qDebug() << "! ActionBack";
  appState_->undoSwitchBrowsedDir();
}

} // namespace qt_file_explorer::gui
