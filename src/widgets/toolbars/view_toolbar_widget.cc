#include "view_toolbar_widget.h"

#include <QPushButton>
#include <QSettings>

#include "toolbar_commons.h"

namespace qt_file_explorer::widgets {

ViewToolbarWidget::ViewToolbarWidget() {
  qDebug() << "+" << this;
}

ViewToolbarWidget::~ViewToolbarWidget() {
  qDebug() << "~" << this;
}

void
ViewToolbarWidget::init(const QSharedPointer<app_state::AppState>& appState) {
  applyCommonToolbarConfiguration(this, "view_toolbar");

  // TODO: shortcut
  auto* togglePreviewButton = new QPushButton("(placeholder)");
  connect(togglePreviewButton, &QPushButton::clicked, [=]() {
    appState->togglePreviewVisible();
  });
  // TODO: persist whether preview was shown or not
  connect(appState.data(), &app_state::AppState::signalPreviewVisibleChanged,
          [=]() {
            togglePreviewButton->setText(
                appState->isPreviewVisible() ? "Hide preview"
                                             : "Show preview");
          });
  addWidget(togglePreviewButton);

  // TODO: shortcut. The `&R` does not work, apparently
  auto* resetLayoutButton = new QPushButton("&Reset layout");
  connect(resetLayoutButton, &QPushButton::clicked, [=]() {
    emit signalResetLayoutClicked();
  });
  addWidget(resetLayoutButton);
}

} // namespace qt_file_explorer::widgets
