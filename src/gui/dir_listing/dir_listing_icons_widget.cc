#include "dir_listing_icons_widget.h"

#include <QFileSystemModel>
#include <QLayout>
#include <QListView>
#include <QStandardPaths>

namespace qt_file_explorer::gui {

// TODO: bind to preview

// TODO: preserve selection between modes

DirListingIconsWidget::DirListingIconsWidget() {
  qDebug() << "+" << this;
}

DirListingIconsWidget::~DirListingIconsWidget() {
  qDebug() << "~" << this;
}

void
DirListingIconsWidget::init(
    const QSharedPointer<DirListingSharedModel>& model,
    const QSharedPointer<app_state::AppState>& appState) {
  model_ = model;
  appState_ = appState;

  setModel(model_.get());

  setViewMode(ViewMode::IconMode);
  setWrapping(true);
  setWordWrap(false);
  // TODO: how does this grid size behave on various DPI/zoom, also across various OSes?
  setGridSize(QSize(72, 56));
  setResizeMode(QListView::Adjust);

  connect(appState_.data(), &app_state::AppState::signalBrowsedDirChanged, this,
          &DirListingIconsWidget::slotBrowsedDirChanged);

  connect(this, &DirListingIconsWidget::doubleClicked,
          [=](const QModelIndex& index) {
            const QFileInfo& fileInfo = model_->fileInfo(index);
            if (fileInfo.isDir()) {
              appState_->switchBrowsedDirTo(fileInfo.filePath());
            }
          });
}

void DirListingIconsWidget::slotBrowsedDirChanged() {
  auto dir = appState_->browsedDir();
  model_->setRootPath(dir);
  setRootIndex(model_->index(dir));
}

void DirListingIconsWidget::currentChanged(const QModelIndex& current,
                                           const QModelIndex& previous) {
  appState_->switchSelectedPathTo(model_->filePath(current));
}

void DirListingIconsWidget::focusInEvent(QFocusEvent* event) {
  // Handling a case of nothing being selected in the listing view.
  //
  // Example 1:
  // - app starts
  // - a dir is selected in the picker component
  // - the user <Tab>s into that dir's listing (this component here)
  // - nothing is selected, while they would rather expect a first time to be selected
  //
  // Example 2:
  // - a file is selected
  // - the user uses "Go to: Home" action
  // - listing changes, nothing is selected
  // - the user <Tab>s into the listing
  //
  bool isNothingSelected = selectedIndexes().isEmpty();
  bool areItemsAvailable = !model_->rootDirectory().isEmpty(model_->filter());
  if (isNothingSelected && areItemsAvailable) {
    qDebug()
        << "[DirListingIconsWidget] nothing was selected -> select the first item";
    auto firstItemModelIndex = model_->index(0, 0, rootIndex());
    setCurrentIndex(firstItemModelIndex);
    selectionModel()->select(firstItemModelIndex,
                             QItemSelectionModel::SelectionFlag::ClearAndSelect |
                             QItemSelectionModel::SelectionFlag::Rows);
  }

  QListView::focusInEvent(event);
}

} // namespace qt_file_explorer::gui
