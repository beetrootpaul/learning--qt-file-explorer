#include "main_window.h"

#include <QApplication>
#include <QCloseEvent>
#include <QDockWidget>
#include <QImage>
#include <QImageReader>
#include <QPainter>
#include <QSettings>

#include "../persisted_state/persisted_state_keys.h"
#include "dir_picker/dir_picker_widget.h"
#include "preview/image_preview_widget.h"
#include "preview/preview_dock_widget.h"

namespace qt_file_explorer::widgets {

// TODO: check the whole `tr(…)` stuff and menus from e.g. https://doc.qt.io/qt-6.2/qtwidgets-widgets-imageviewer-example.html

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

// TODO: tabbing order

void MainWindow::init(const QSharedPointer<app_state::AppState>& appState) {
  appState_ = appState;

  setWindowTitle("Qt File Explorer");

  splitter_ = new QSplitter();
  setCentralWidget(splitter_);

  auto* dirPicker = new DirPickerWidget();
  dirPicker->init(appState);

  // TODO: keep selection between view types
  dirListingSharedModel_ = QSharedPointer<DirListingSharedModel>(
      new DirListingSharedModel());
  dirListingList_ = new DirListingListWidget();
  dirListingList_->init(dirListingSharedModel_, appState);
  dirListingIcons_ = new DirListingIconsWidget();
  dirListingIcons_->init(dirListingSharedModel_, appState);
  connect(appState.data(), &app_state::AppState::signalViewTypeChanged, this,
          &MainWindow::slotViewTypeChanged);

  splitter_->setOrientation(Qt::Orientation::Horizontal);
  splitter_->addWidget(dirPicker);
  splitter_->setStretchFactor(0, 1);
  splitter_->addWidget(dirListingList_);
  splitter_->setStretchFactor(1, 2);

  // TODO: initial size of the preview/dock

  previewDock_ = new PreviewDockWidget();
  previewDock_->init(appState);
  connect(appState.data(), &app_state::AppState::signalPreviewVisibleChanged,
          this, &MainWindow::slotPreviewVisibleChanged);
  addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, previewDock_);

  historyToolbar_ = new HistoryToolbarWidget();
  historyToolbar_->init(appState);
  addToolBar(Qt::ToolBarArea::TopToolBarArea, historyToolbar_);

  navigationToolbar_ = new NavigationToolbarWidget();
  navigationToolbar_->init(appState);
  connect(navigationToolbar_,
          &NavigationToolbarWidget::signalCollapseAllLicked,
          [=]() {
            dirPicker->collapseAll();
          });
  addToolBar(Qt::ToolBarArea::TopToolBarArea, navigationToolbar_);

  viewToolbar_ = new ViewToolbarWidget();
  viewToolbar_->init(appState);
  connect(viewToolbar_, &ViewToolbarWidget::signalResetLayoutClicked,
          [=]() {
            QSettings settings;
            settings.remove(persisted_state::PersistedStateKeys::groupLayout);
            resetMainWindowLayout();
            resetSplitterLayout();
          });
  addToolBar(Qt::ToolBarArea::TopToolBarArea, viewToolbar_);

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
    // TODO: consider this: QGuiApplication::primaryScreen()->availableSize() * 3 / 5
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
      persisted_state::PersistedStateKeys::splitterState).toByteArray();
  if (!splitterState.isEmpty()) {
    splitter_->restoreState(splitterState);
  } else {
    resetSplitterLayout();
  }
}

void MainWindow::resetMainWindowLayout() {
  qDebug() << "MainWindow::resetMainWindowLayout";

  addToolBar(Qt::ToolBarArea::TopToolBarArea, historyToolbar_);
  addToolBar(Qt::ToolBarArea::TopToolBarArea, navigationToolbar_);
  addToolBar(Qt::ToolBarArea::TopToolBarArea, viewToolbar_);

  // TODO: make the show/hide button adapt to dock being closed

  previewDock_->setFloating(false);
  addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, previewDock_);
}

// TODO: trigger it also on a double click on the splitter bar
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
    }
  } else {
    if (splitter_->widget(1) != dirListingIcons_) {
      splitter_->replaceWidget(1, dirListingIcons_);
      // Stretch factor is bound to a specific sub-widget, therefore
      // we have to make sure it is applied on this one as well,
      // if it was not set on this particular widget yet.
      splitter_->setStretchFactor(1, 2);
    }
  };
}

void MainWindow::slotPreviewVisibleChanged() {
  if (appState_->isPreviewVisible()) {
    previewDock_->show();
  } else {
    previewDock_->hide();
  }
}

} // namespace qt_file_explorer::widgets
