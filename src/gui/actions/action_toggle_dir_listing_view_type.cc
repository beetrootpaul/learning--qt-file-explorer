#include "action_toggle_dir_listing_view_type.h"

namespace qt_file_explorer::gui {

ActionToggleDirListingViewType::ActionToggleDirListingViewType(QObject* parent,
                                                               const QSharedPointer<app_state::AppState>& appState)
    : QAction(parent), appState_(appState) {
  setObjectName("ActionToggleDirListingViewType");

  qDebug() << "+" << this;

  setText(tr("(placeholder)"));
  // TODO: centralize shortcuts
  setShortcut(Qt::META | Qt::Key_V);

  connect(appState_.data(), &app_state::AppState::signalViewTypeChanged, [=]() {
    setText(tr(appState->currentDirListingViewType() ==
               app_state::DirListingViewType::List ? "&Switch to icons"
                                                   : "&Switch to list"));
  });

  connect(this, &QAction::triggered, this,
          &ActionToggleDirListingViewType::perform);
}

ActionToggleDirListingViewType::~ActionToggleDirListingViewType() {
  qDebug() << "~" << this;
}

void ActionToggleDirListingViewType::perform() {
  qDebug() << "! ActionToggleDirListingViewType";
  appState_->toggleDirListingViewType();
}

} // namespace qt_file_explorer::gui
