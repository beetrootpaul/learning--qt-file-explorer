#include "navigation_toolbar_widget.h"

#include <QDebug>
#include <QPushButton>

#include "../toolbar_commons.h"

namespace qt_file_explorer::widgets {

NavigationToolbarWidget::NavigationToolbarWidget() {
  qDebug() << "+" << this;
}

NavigationToolbarWidget::~NavigationToolbarWidget() {
  qDebug() << "~" << this;
}

void
NavigationToolbarWidget::init(
    const QSharedPointer<app_state::AppState>& appState) {
  applyCommonToolbarConfiguration(this, "navigation_toolbar");

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
