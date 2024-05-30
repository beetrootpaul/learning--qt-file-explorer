#include "action_quick_open_downloads.h"

#include "../../shortcuts.h"

namespace qt_file_explorer::gui {

ActionQuickOpenDownloads::ActionQuickOpenDownloads(QObject* parent,
                                                   const QSharedPointer<app_state::AppState>& appState)
    : QAction(parent), appState_(appState) {
  setObjectName("ActionQuickOpenDownloads");

  qDebug() << "+" << this;

  setText(tr("Go to: Downloads"));
  setShortcut(Shortcuts::goToDownloads());

  connect(this, &QAction::triggered, this, &ActionQuickOpenDownloads::perform);
}

ActionQuickOpenDownloads::~ActionQuickOpenDownloads() {
  qDebug() << "~" << this;
}

void ActionQuickOpenDownloads::perform() {
  qDebug() << "! ActionQuickOpenDownloads";
  appState_->switchBrowsedDirToDownloads();
}

} // namespace qt_file_explorer::gui
