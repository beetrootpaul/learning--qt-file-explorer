#include "main_window.h"

#include <QApplication>
#include <QCloseEvent>
#include <QSettings>
#include <QToolBar>

#include "../persisted_state/persisted_state_keys.h"
#include "directory_picker_widget.h"

namespace qt_file_explorer::widgets {

MainWindow::MainWindow() {
  qDebug() << "+" << this;
}

MainWindow::~MainWindow() {
  qDebug() << "~" << this;

  // We keep only one listing type visible at the time. The other one is not
  // attached to a widget tree managed by Qt. Therefore we have to delete
  // that other one manually.
  if (splitter_->widget(1) != directoryListingList_) {
    delete directoryListingList_;
  }
  if (splitter_->widget(1) != directoryListingIcons_) {
    delete directoryListingIcons_;
  }
}

// TODO: tabbing order

void MainWindow::init(const QSharedPointer<app_state::AppState>& appState) {
  appState_ = appState;

  setWindowTitle("Qt File Explorer");

  splitter_ = new QSplitter();
  setCentralWidget(splitter_);

  auto* directoryPicker = new DirectoryPickerWidget();
  directoryPicker->init(appState);

  // TODO: keep selection between view types

  directoryListingSharedModel_ = QSharedPointer<DirectoryListingSharedModel>(
      new DirectoryListingSharedModel());
  directoryListingList_ = new DirectoryListingListWidget();
  directoryListingList_->init(directoryListingSharedModel_, appState);
  directoryListingIcons_ = new DirectoryListingIconsWidget();
  directoryListingIcons_->init(directoryListingSharedModel_, appState);
  connect(appState.data(), &app_state::AppState::signalViewTypeChanged, this,
          &MainWindow::slotViewTypeChanged);

  splitter_->setOrientation(Qt::Orientation::Horizontal);
  splitter_->addWidget(directoryPicker);
  splitter_->setStretchFactor(0, 1);
  splitter_->addWidget(directoryListingList_);
  splitter_->setStretchFactor(1, 2);

  historyToolbar_ = new HistoryToolbarWidget();
  historyToolbar_->init(appState);
  addToolBar(Qt::ToolBarArea::TopToolBarArea, historyToolbar_);

  navigationToolbar_ = new NavigationToolbarWidget();
  navigationToolbar_->init(appState);
  connect(navigationToolbar_,
          &NavigationToolbarWidget::signalCollapseAllLicked,
          [=]() {
            directoryPicker->collapseAll();
          });
  addToolBar(Qt::ToolBarArea::TopToolBarArea, navigationToolbar_);

  viewToolbar_ = new ViewToolbarWidget();
  viewToolbar_->init();
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
  addToolBar(Qt::ToolBarArea::TopToolBarArea, historyToolbar_);
  addToolBar(Qt::ToolBarArea::TopToolBarArea, navigationToolbar_);
  addToolBar(Qt::ToolBarArea::TopToolBarArea, viewToolbar_);
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
    if (splitter_->widget(1) != directoryListingList_) {
      splitter_->replaceWidget(1, directoryListingList_);
      // Stretch factor is bound to a specific sub-widget, therefore
      // we have to make sure it is applied on this one as well.
      splitter_->setStretchFactor(1, 2);
    }
  } else {
    if (splitter_->widget(1) != directoryListingIcons_) {
      splitter_->replaceWidget(1, directoryListingIcons_);
      // Stretch factor is bound to a specific sub-widget, therefore
      // we have to make sure it is applied on this one as well.
      splitter_->setStretchFactor(1, 2);
    }
  };
}

} // namespace qt_file_explorer::widgets
