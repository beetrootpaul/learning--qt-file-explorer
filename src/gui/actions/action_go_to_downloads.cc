#include "action_go_to_downloads.h"

#include "../../shortcuts.h"

namespace qt_file_explorer::gui {

ActionGoToDownloads::ActionGoToDownloads(QObject* parent,
                                         app_state::AppState* appState)
    : QAction(parent), appState_(appState) {
  setObjectName("ActionGoToDownloads");

  qDebug() << "+" << this;

  setText(tr("Go to: Downloads"));
  setShortcut(Shortcuts::goToDownloads());

  connect(this, &QAction::triggered, this, &ActionGoToDownloads::perform);
}

ActionGoToDownloads::~ActionGoToDownloads() {
  qDebug() << "~" << this;
}

void ActionGoToDownloads::perform() {
  qDebug() << "! ActionGoToDownloads";
  appState_->switchBrowsedDirToDownloads();
}

} // namespace qt_file_explorer::gui
