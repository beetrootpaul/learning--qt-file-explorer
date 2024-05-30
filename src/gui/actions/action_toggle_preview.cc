#include "action_toggle_preview.h"

namespace qt_file_explorer::gui {

ActionTogglePreview::ActionTogglePreview(QObject* parent,
                                         const QSharedPointer<app_state::AppState>& appState)
    : QAction(parent), appState_(appState) {
  setObjectName("ActionTogglePreview");

  qDebug() << "+" << this;

  setText(tr("(placeholder)"));
  // TODO: centralize shortcuts
  setShortcut(Qt::META | Qt::Key_P);

  connect(appState_.data(), &app_state::AppState::signalPreviewVisibleChanged,
          [=]() {
            setText(tr(appState->isPreviewVisible() ? "Hide preview"
                                                    : "Show preview"));
          });

  connect(this, &QAction::triggered, this, &ActionTogglePreview::perform);
}

ActionTogglePreview::~ActionTogglePreview() {
  qDebug() << "~" << this;
}

void ActionTogglePreview::perform() {
  qDebug() << "! ActionTogglePreview";
  appState_->togglePreviewVisible();
}

} // namespace qt_file_explorer::gui
