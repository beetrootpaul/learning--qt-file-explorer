#include "main_window.h"

#include <iostream>

#include <QApplication>
#include <QCloseEvent>
#include <QPushButton>
#include <QScreen>
#include <QSettings>
#include <QToolBar>

#include "directory_listing_widget.h"
#include "directory_picker_widget.h"

namespace qt_file_explorer::widgets {

MainWindow::MainWindow() {
  qDebug() << "+" << this;
}

MainWindow::~MainWindow() {
  qDebug() << "~" << this;
}

void MainWindow::init(QSharedPointer<app_state::AppState> appState) {
  appState_ = appState;

  setWindowTitle("Qt File Explorer");

  splitter_ = new QSplitter();
  setCentralWidget(splitter_);

  auto* directoryPicker = new DirectoryPickerWidget();
  directoryPicker->init(appState);
  auto* directoryListing = new DirectoryListingWidget();
  directoryListing->init(appState);

  splitter_->setOrientation(Qt::Orientation::Horizontal);
  splitter_->addWidget(directoryPicker);
  splitter_->setStretchFactor(0, 1);
  splitter_->addWidget(directoryListing);
  splitter_->setStretchFactor(1, 2);

  // TODO: tabbing order

  // TODO: shortcut. The `&H` does not work, apparently
  auto* quickOpenHomeButton = new QPushButton("Quick open: &Home");
  connect(quickOpenHomeButton, &QPushButton::clicked, [=]() {
    appState->switchPathToHome();
  });

  // TODO: shortcut. The `&D` does not work, apparently
  auto* quickOpenDownloadsButton = new QPushButton("Quick open: &Downloads");
  connect(quickOpenDownloadsButton, &QPushButton::clicked, [=]() {
    appState->switchPathToDownloads();
  });

  // TODO: shortcut. The `&R` does not work, apparently
  auto* resetLayoutButton = new QPushButton("&Reset layout");
  connect(resetLayoutButton, &QPushButton::clicked, [=]() {
    QSettings settings;
    settings.remove("v3/layout/");
    resetMainWindowLayout();
    resetSplitterLayout();
  });

  // TODO: shortcut. The `&S` does not work, apparently
  toggleDirListingViewTypeButton_ = new QPushButton("(placeholder)");
  connect(toggleDirListingViewTypeButton_, &QPushButton::clicked, [=]() {
    appState->toggleDirListingViewType();
  });
  connect(appState.data(), &app_state::AppState::signalChanged, this,
          &MainWindow::slotAppStateChanged);

  toolbar_ = new QToolBar();
  // Object name is required for state serialization
  toolbar_->setObjectName("main_toolbar");
  toolbar_->addWidget(quickOpenHomeButton);
  toolbar_->addWidget(quickOpenDownloadsButton);
  toolbar_->addWidget(resetLayoutButton);
  toolbar_->addWidget(toggleDirListingViewTypeButton_);

  toolbar_->setMovable(true);
  toolbar_->setFloatable(false);

  // Remove context menu in order to remove the ability to close this toolbar_
  toolbar_->setContextMenuPolicy(Qt::ContextMenuPolicy::PreventContextMenu);

  addToolBar(Qt::ToolBarArea::TopToolBarArea, toolbar_);

  appState->loadPersistedState();
  loadPersistedState();
}

void MainWindow::closeEvent(QCloseEvent* event) {
  appState_->savePersistedState();
  savePersistedState();

  event->accept();
}

void MainWindow::slotAppStateChanged() {
  toggleDirListingViewTypeButton_->setText(
      appState_->currentDirListingViewType() ==
      app_state::DirListingViewType::List ? "&Switch to icons"
                                          : "&Switch to list");
}

void MainWindow::savePersistedState() {
  QSettings settings;

  // TODO: extract key constants
  settings.setValue("v3/window/main_window/size", size());
  settings.setValue("v3/window/main_window/pos", pos());
  settings.setValue("v3/layout/main_window/state", saveState());
  settings.setValue("v3/layout/splitter/state", splitter_->saveState());
}

void MainWindow::loadPersistedState() {
  QSettings settings;

  const auto mainWindowSize = settings.value(
      "v3/window/main_window/size").toSize();
  if (!mainWindowSize.isEmpty()) {
    resize(mainWindowSize);
  } else {
    resize(800, 600);
  }

  const auto mainWindowPos = settings.value(
      "v3/window/main_window/pos").toPoint();
  if (!mainWindowPos.isNull()) {
    move(mainWindowPos);
  } else {
    int desired_pos_x =
        (screen()->availableGeometry().width() - width()) / 2;
    int desired_pos_y =
        (screen()->availableGeometry().height() - height()) / 2;
    move(desired_pos_x, desired_pos_y);
  }

  const auto mainWindowState = settings.value(
      "v3/layout/main_window/state").toByteArray();
  if (!mainWindowState.isEmpty()) {
    restoreState(mainWindowState);
  } else {
    resetMainWindowLayout();
  }

  const auto splitterState = settings.value(
      "v3/layout/splitter/state").toByteArray();
  if (!splitterState.isEmpty()) {
    splitter_->restoreState(splitterState);
  } else {
    resetSplitterLayout();
  }
}

void MainWindow::resetMainWindowLayout() {
  addToolBar(Qt::ToolBarArea::TopToolBarArea, toolbar_);
}

// TODO: trigger it also on a double click on the splitter bar
void MainWindow::resetSplitterLayout() {
  int stretchTotal = 0;
  for (int i = 0; i < splitter_->count(); ++i) {
    stretchTotal += splitter_->widget(i)->sizePolicy().horizontalStretch();
  }

  auto desiredSizes = QList<int>(splitter_->count());
  int desiredWidthsAccumulated = 0;
  for (int i = 0; i < splitter_->count(); ++i) {
    auto* widget = splitter_->widget(i);
    int stretch = widget->sizePolicy().horizontalStretch();
    float ratio =
        static_cast<float>(stretch) / static_cast<float>(stretchTotal);
    int totalWidth = splitter_->width();
    int desiredWidth = std::floor(static_cast<float>(totalWidth) * ratio);
    if (i == splitter_->count() - 1) {
      desiredWidth = width() - desiredWidthsAccumulated;
    }
    desiredWidthsAccumulated += desiredWidth;
    desiredSizes[i] = desiredWidth;
  }
  splitter_->setSizes(desiredSizes);
}

} // namespace qt_file_explorer::widgets
