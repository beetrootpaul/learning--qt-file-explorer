#include "history_toolbar_widget.h"

#include <QDebug>
#include <QPushButton>

#include "toolbar_commons.h"

namespace qt_file_explorer::gui {

HistoryToolbarWidget::HistoryToolbarWidget() {
  qDebug() << "+" << this;
}

HistoryToolbarWidget::~HistoryToolbarWidget() {
  qDebug() << "~" << this;
}

void
HistoryToolbarWidget::init(
    const QSharedPointer<app_state::AppState>& appState) {
  applyCommonToolbarConfiguration(this, "history_toolbar");

  // TODO: enabled if anything to undo
  // TODO: shortcut
  auto* undoNavigationButton = new QPushButton("Undo navigation");
  connect(undoNavigationButton, &QPushButton::clicked, [=]() {
    appState->undoSwitchBrowsedDir();
  });
  addWidget(undoNavigationButton);

  // TODO: enabled if anything to redo
  // TODO: shortcut
  auto* redoNavigationButton = new QPushButton("Redo navigation");
  connect(redoNavigationButton, &QPushButton::clicked, [=]() {
    appState->redoSwitchBrowsedDir();
  });
  addWidget(redoNavigationButton);
}

} // namespace qt_file_explorer::gui
