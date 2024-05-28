#include "main_toolbar.h"

#include <QDebug>
#include <QPushButton>

#include "toolbar_commons.h"

namespace qt_file_explorer::widgets {

MainToolbar::MainToolbar() {
  qDebug() << "+" << this;
}

MainToolbar::~MainToolbar() {
  qDebug() << "~" << this;
}

void MainToolbar::init(const QSharedPointer<app_state::AppState>& appState) {
  applyCommonToolbarConfiguration(this, "main_toolbar");

  // TODO: enabled if anything to undo
  // TODO: shortcut
  auto* undoNavigationButton = new QPushButton("Undo navigation");
  connect(undoNavigationButton, &QPushButton::clicked, [=]() {
    appState->undoSwitchPath();
  });
  addWidget(undoNavigationButton);

  // TODO: enabled if anything to redo
  // TODO: shortcut
  auto* redoNavigationButton = new QPushButton("Redo navigation");
  connect(redoNavigationButton, &QPushButton::clicked, [=]() {
    appState->redoSwitchPath();
  });
  addWidget(redoNavigationButton);

  // TODO: shortcut. The `&C` does not work, apparently
  auto* collapseAllButton = new QPushButton("&Collapse all");
  connect(collapseAllButton, &QPushButton::clicked, [=]() {
    emit signalCollapseAllLicked();
  });
  addWidget(collapseAllButton);

  // TODO: shortcut. The `&H` does not work, apparently
  auto* quickOpenHomeButton = new QPushButton("Quick open: &Home");
  connect(quickOpenHomeButton, &QPushButton::clicked, [=]() {
    appState->switchPathToHome();
  });
  addWidget(quickOpenHomeButton);

  // TODO: shortcut. The `&D` does not work, apparently
  auto* quickOpenDownloadsButton = new QPushButton("Quick open: &Downloads");
  connect(quickOpenDownloadsButton, &QPushButton::clicked, [=]() {
    appState->switchPathToDownloads();
  });
  addWidget(quickOpenDownloadsButton);

  // TODO: shortcut. The `&S` does not work, apparently
  auto* toggleDirListingViewTypeButton = new QPushButton("(placeholder)");
  connect(toggleDirListingViewTypeButton, &QPushButton::clicked, [=]() {
    appState->toggleDirListingViewType();
  });
  connect(appState.data(), &app_state::AppState::signalViewTypeChanged, [=]() {
    toggleDirListingViewTypeButton->setText(
        appState->currentDirListingViewType() ==
        app_state::DirListingViewType::List ? "&Switch to icons"
                                            : "&Switch to list");
  });
  addWidget(toggleDirListingViewTypeButton);
}

} // namespace qt_file_explorer::widgets
