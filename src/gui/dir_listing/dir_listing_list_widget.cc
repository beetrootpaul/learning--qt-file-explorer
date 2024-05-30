#include "dir_listing_list_widget.h"

#include <QFileSystemModel>
#include <QKeyEvent>
#include <QHeaderView>
#include <QSettings>
#include <QStandardPaths>

#include "../../persisted_state/persisted_state_keys.h"

namespace qt_file_explorer::gui {

DirListingListWidget::DirListingListWidget() {
  qDebug() << "+" << this;
}

DirListingListWidget::~DirListingListWidget() {
  qDebug() << "~" << this;
}

void
DirListingListWidget::init(
    const QSharedPointer<DirListingSharedModel>& model,
    const QSharedPointer<app_state::AppState>& appState) {
  model_ = model;
  appState_ = appState;

  setModel(model_.get());

  // Make this tree look like a regular flat list
  setRootIsDecorated(false);
  setItemsExpandable(false);

  setSortingEnabled(true);

  connect(appState_.data(), &app_state::AppState::signalBrowsedDirChanged, this,
          &DirListingListWidget::slotBrowsedDirChanged);

  connect(this, &QTreeView::doubleClicked, [=](const QModelIndex& index) {
    const QFileInfo& fileInfo = model_->fileInfo(index);
    if (fileInfo.isDir()) {
      appState_->switchBrowsedDirTo(fileInfo.filePath());
    }
  });
}

void DirListingListWidget::savePersistedState() {
  QSettings settings;

  settings.setValue(persisted_state::PersistedStateKeys::listingListHeaderState,
                    header()->saveState());
}

void DirListingListWidget::loadPersistedState() {
  QSettings settings;

  if (settings.contains(
      persisted_state::PersistedStateKeys::listingListHeaderState)) {
    auto headerState = settings.value(
        persisted_state::PersistedStateKeys::listingListHeaderState).toByteArray();
    header()->restoreState(headerState);
  } else {
    // Sort by "Name" column
    sortByColumn(0, Qt::SortOrder::AscendingOrder);
  }
}

// TODO: do the same for icons view
void DirListingListWidget::currentChanged(const QModelIndex& current,
                                          const QModelIndex& previous) {
  appState_->switchSelectedPathTo(model_->filePath(current));
}

void DirListingListWidget::focusInEvent(QFocusEvent* event) {
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
        << "[DirListingListWidget] nothing was selected -> select the first item";
    auto firstItemModelIndex = model_->index(0, 0, rootIndex());
    setCurrentIndex(firstItemModelIndex);
    selectionModel()->select(firstItemModelIndex,
                             QItemSelectionModel::SelectionFlag::ClearAndSelect |
                             QItemSelectionModel::SelectionFlag::Rows);
  }

  QTreeView::focusInEvent(event);
}

void DirListingListWidget::slotBrowsedDirChanged() {
  auto dir = appState_->browsedDir();
  model_->setRootPath(dir);
  setRootIndex(model_->index(dir));
  clearSelection();
}

} // namespace qt_file_explorer::gui
