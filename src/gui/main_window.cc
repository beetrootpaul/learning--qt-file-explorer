#include "main_window.h"

#include <QApplication>
#include <QCloseEvent>
#include <QDockWidget>
#include <QImage>
#include <QImageReader>
#include <QMenuBar>
#include <QPainter>
#include <QSettings>

#include "../persisted_state/persisted_state_keys.h"
#include "actions/action_collapse_all.h"
#include "actions/action_forward.h"
#include "actions/action_back.h"
#include "actions/action_toggle_dir_listing_view_type.h"
#include "actions/action_toggle_preview.h"
#include "actions/action_go_to_downloads.h"
#include "actions/action_go_to_home.h"
#include "actions/action_reset_layout.h"

namespace qt_file_explorer::gui {

MainWindow::MainWindow() {
  qDebug() << "+" << this;
}

MainWindow::~MainWindow() {
  qDebug() << "~" << this;

  // We keep only one listing type visible at the time. The other one is not
  // attached to a widget tree managed by Qt. Therefore we have to delete
  // that other one manually.
  if (splitter_->widget(1) != dirListingList_) {
    delete dirListingList_;
  }
  if (splitter_->widget(1) != dirListingIcons_) {
    delete dirListingIcons_;
  }
}

void MainWindow::init(const QSharedPointer<app_state::AppState>& appState) {
  appState_ = appState;

  setWindowTitle(tr("Qt File Explorer"));

  initSplitter();
  initPreview();

  actionBack_ = new ActionBack(this, appState_);
  actionForward_ = new ActionForward(this, appState_);
  actionCollapseAll_ = new ActionCollapseAll(this, dirPicker_);
  actionGoToHome_ = new ActionGoToHome(this, appState_);
  actionGoToDownloads_ = new ActionGoToDownloads(this, appState_);
  actionToggleDirListingViewType_ = new ActionToggleDirListingViewType(this,
                                                                       appState_);
  actionTogglePreview_ = new ActionTogglePreview(this, appState_);
  actionResetLayout_ = new ActionResetLayout(this, this);
  initToolbars();
  initMenus();

  appState_->loadPersistedState();
  dirListingList_->loadPersistedState();
  loadPersistedState();
}

void MainWindow::initSplitter() {
  splitter_ = new QSplitter();
  setCentralWidget(splitter_);

  dirPicker_ = new DirPickerWidget();
  dirPicker_->init(appState_);

  dirListingSharedModel_ = QSharedPointer<DirListingSharedModel>(
      new DirListingSharedModel());

  dirListingList_ = new DirListingListWidget();
  dirListingList_->init(dirListingSharedModel_, appState_);

  dirListingIcons_ = new DirListingIconsWidget();
  dirListingIcons_->init(dirListingSharedModel_, appState_);

  connect(appState_.data(), &app_state::AppState::signalViewTypeChanged, this,
          &MainWindow::slotViewTypeChanged);

  splitter_->setOrientation(Qt::Orientation::Horizontal);
  splitter_->addWidget(dirPicker_);
  splitter_->setStretchFactor(0, 1);
  splitter_->addWidget(dirListingList_);
  splitter_->setStretchFactor(1, 2);
}

void MainWindow::initPreview() {
  previewDock_ = new PreviewDockWidget();
  previewDock_->init(appState_);
  connect(appState_.data(), &app_state::AppState::signalPreviewVisibleChanged,
          this, &MainWindow::slotPreviewVisibleChanged);
  addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, previewDock_);
}

void MainWindow::initToolbars() {
  toolbarNavigation_ = new Toolbar("navigation_toolbar");
  toolbarNavigation_->addAction(actionCollapseAll_);
  toolbarNavigation_->addSeparator();
  toolbarNavigation_->addAction(actionGoToHome_);
  toolbarNavigation_->addAction(actionGoToDownloads_);
  toolbarNavigation_->addSeparator();
  toolbarNavigation_->addAction(actionBack_);
  toolbarNavigation_->addAction(actionForward_);
  addToolBar(Qt::ToolBarArea::TopToolBarArea, toolbarNavigation_);

  toolbarView_ = new Toolbar("navigation_toolbar");
  toolbarView_->addAction(actionToggleDirListingViewType_);
  toolbarView_->addAction(actionTogglePreview_);
  addToolBar(Qt::ToolBarArea::TopToolBarArea, toolbarView_);
}

void MainWindow::initMenus() {
  auto* menuNavigation = menuBar()->addMenu(tr("Navigation"));
  menuNavigation->addAction(actionCollapseAll_);
  menuNavigation->addSeparator();
  menuNavigation->addAction(actionGoToHome_);
  menuNavigation->addAction(actionGoToDownloads_);
  menuNavigation->addSeparator();
  menuNavigation->addAction(actionBack_);
  menuNavigation->addAction(actionForward_);

  // NOTE: Keeping the name "View" makes Qt add "Full screen" action
  // out of the box (observed on macOS Sonoma).
  auto* menuView = menuBar()->addMenu(tr("View"));
  menuView->addAction(actionToggleDirListingViewType_);
  menuView->addAction(actionTogglePreview_);

  auto* menuLayout = menuBar()->addMenu(tr("Layout"));
  menuLayout->addAction(actionResetLayout_);
}

void MainWindow::closeEvent(QCloseEvent* event) {
  appState_->savePersistedState();
  dirListingList_->savePersistedState();
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
  settings.setValue(persisted_state::PersistedStateKeys::splitterState,
                    splitter_->saveState());
}

void MainWindow::loadPersistedState() {
  QSettings settings;

  const auto mainWindowSize = settings.value(
      persisted_state::PersistedStateKeys::mainWindowSize).toSize();
  if (!mainWindowSize.isEmpty()) {
    resize(mainWindowSize);
  } else {
    resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
  }

  const auto mainWindowPos = settings.value(
      persisted_state::PersistedStateKeys::mainWindowPos).toPoint();
  if (!mainWindowPos.isNull()) {
    move(mainWindowPos);
  } else {
    move((screen()->availableGeometry().width() - width()) / 2,
         (screen()->availableGeometry().height() - height()) / 2);
  }

  const auto mainWindowState = settings.value(
      persisted_state::PersistedStateKeys::mainWindowState).toByteArray();
  if (!mainWindowState.isEmpty()) {
    restoreState(mainWindowState);
  } else {
    resetMainWindowLayout();
  }

  const auto splitterState = settings.value(
      persisted_state::PersistedStateKeys::splitterState).toByteArray();
  if (!splitterState.isEmpty()) {
    splitter_->restoreState(splitterState);
  } else {
    resetSplitterLayout();
  }
}

void MainWindow::resetLayout() {
  QSettings settings;
  settings.remove(persisted_state::PersistedStateKeys::groupResettableLayout);
  resetMainWindowLayout();
  resetSplitterLayout();
}

void MainWindow::resetMainWindowLayout() {
  qDebug() << "MainWindow::resetMainWindowLayout";

  addToolBar(Qt::ToolBarArea::TopToolBarArea, toolbarNavigation_);
  addToolBar(Qt::ToolBarArea::TopToolBarArea, toolbarView_);

  // Make it docked in case it was floating
  previewDock_->setFloating(false);

  addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, previewDock_);
  resizeDocks(QList<QDockWidget*>{previewDock_}, QList<int>{size().width() / 3},
              Qt::Orientation::Horizontal);
}

void MainWindow::resetSplitterLayout() {
  qDebug() << "MainWindow::resetSplitterLayout";

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
      desiredWidth = totalWidth - desiredWidthsAccumulated;
    }
    desiredWidthsAccumulated += desiredWidth;
    desiredSizes[i] = desiredWidth;
  }
  splitter_->setSizes(desiredSizes);
}

void MainWindow::slotViewTypeChanged() {
  if (appState_->currentDirListingViewType() ==
      app_state::DirListingViewType::List) {
    if (splitter_->widget(1) != dirListingList_) {
      splitter_->replaceWidget(1, dirListingList_);
      // Stretch factor is bound to a specific sub-widget, therefore
      // we have to make sure it is applied on this one as well,
      // if it was not set on this particular widget yet.
      splitter_->setStretchFactor(1, 2);

      auto selectedIndexes = dirListingIcons_->selectionModel()->selectedIndexes();
      if (!selectedIndexes.isEmpty()) {
        dirListingList_->setCurrentIndex(selectedIndexes.first());
        dirListingList_->selectionModel()->select(selectedIndexes.first(),
                                                  QItemSelectionModel::SelectionFlag::ClearAndSelect);
      }
    }
  } else {
    if (splitter_->widget(1) != dirListingIcons_) {
      splitter_->replaceWidget(1, dirListingIcons_);
      // Stretch factor is bound to a specific sub-widget, therefore
      // we have to make sure it is applied on this one as well,
      // if it was not set on this particular widget yet.
      splitter_->setStretchFactor(1, 2);

      auto selectedIndexes = dirListingList_->selectionModel()->selectedIndexes();
      if (!selectedIndexes.isEmpty()) {
        dirListingIcons_->setCurrentIndex(selectedIndexes.first());
        dirListingIcons_->selectionModel()->select(selectedIndexes.first(),
                                                   QItemSelectionModel::SelectionFlag::ClearAndSelect);
      }
    }
  }
}

void MainWindow::slotPreviewVisibleChanged() {
  if (appState_->isPreviewVisible()) {
    previewDock_->show();
  } else {
    previewDock_->hide();
  }
}

} // namespace qt_file_explorer::gui
