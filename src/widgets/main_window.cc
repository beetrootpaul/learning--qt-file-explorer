#include "main_window.h"

#include <QApplication>
#include <QCloseEvent>
#include <QSettings>
#include <QToolBar>

#include "../persisted_state/persisted_state_keys.h"
#include "directory_listing_widget.h"
#include "directory_picker_widget.h"
#include "layout_toolbar.h"
#include "main_toolbar.h"

namespace qt_file_explorer::widgets {

MainWindow::MainWindow() {
  qDebug() << "+" << this;
}

MainWindow::~MainWindow() {
  qDebug() << "~" << this;
}

// TODO: tabbing order

void MainWindow::init(const QSharedPointer<app_state::AppState>& appState) {
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

  mainToolbar_ = new MainToolbar();
  mainToolbar_->init(appState);
  connect(mainToolbar_, &MainToolbar::signalCollapseAllLicked, [=]() {
    directoryPicker->collapseAll();
  });
  addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolbar_);

  layoutToolbar_ = new LayoutToolbar();
  layoutToolbar_->init();
  connect(layoutToolbar_, &LayoutToolbar::signalResetLayoutClicked, [=]() {
    QSettings settings;
    settings.remove(persisted_state::PersistedStateKeys::groupLayout);
    resetMainWindowLayout();
    resetSplitterLayout();
  });
  addToolBar(Qt::ToolBarArea::TopToolBarArea, layoutToolbar_);

  appState->loadPersistedState();
  loadPersistedState();
}

void MainWindow::closeEvent(QCloseEvent* event) {
  appState_->savePersistedState();
  savePersistedState();

  event->accept();
}

void MainWindow::savePersistedState() {
  QSettings settings;

  settings.setValue(persisted_state::PersistedStateKeys::mainWindowSize,
                    size());
  settings.setValue(persisted_state::PersistedStateKeys::mainWindowPos, pos());
  settings.setValue(persisted_state::PersistedStateKeys::mainWindowState,
                    saveState());
  settings.setValue(persisted_state::PersistedStateKeys::mainWindowState,
                    splitter_->saveState());
}

void MainWindow::loadPersistedState() {
  QSettings settings;

  const auto mainWindowSize = settings.value(
      persisted_state::PersistedStateKeys::mainWindowSize).toSize();
  if (!mainWindowSize.isEmpty()) {
    resize(mainWindowSize);
  } else {
    resize(1200, 800);
  }

  const auto mainWindowPos = settings.value(
      persisted_state::PersistedStateKeys::mainWindowPos).toPoint();
  if (!mainWindowPos.isNull()) {
    move(mainWindowPos);
  } else {
    int desired_pos_x =
        (screen()->availableGeometry().width() - width()) / 2;
    int desired_pos_y =
        (screen()->availableGeometry().height() - height()) / 2;
    move(desired_pos_x, desired_pos_y);
  }

  // TODO: how to make rearrangement of toolbars kept across app runs?
  const auto mainWindowState = settings.value(
      persisted_state::PersistedStateKeys::mainWindowState).toByteArray();
  if (!mainWindowState.isEmpty()) {
    restoreState(mainWindowState);
  } else {
    resetMainWindowLayout();
  }

  const auto splitterState = settings.value(
      persisted_state::PersistedStateKeys::mainWindowState).toByteArray();
  if (!splitterState.isEmpty()) {
    splitter_->restoreState(splitterState);
  } else {
    resetSplitterLayout();
  }
}

void MainWindow::resetMainWindowLayout() {
  addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolbar_);
  addToolBar(Qt::ToolBarArea::TopToolBarArea, layoutToolbar_);
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
