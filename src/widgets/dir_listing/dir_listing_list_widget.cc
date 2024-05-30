#include "dir_listing_list_widget.h"

#include <QFileSystemModel>
#include <QKeyEvent>
#include <QStandardPaths>

namespace qt_file_explorer::widgets {

DirListingListWidget::DirListingListWidget() {
  qDebug() << "+" << this;
}

DirListingListWidget::~DirListingListWidget() {
  qDebug() << "~" << this;
}

// TODO: sorting by columns

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

  connect(appState_.data(), &app_state::AppState::signalBrowsedDirChanged, this,
          &DirListingListWidget::slotBrowsedDirChanged);

  connect(this, &QTreeView::doubleClicked, [=](const QModelIndex& index) {
    const QFileInfo& fileInfo = model_->fileInfo(index);
    if (fileInfo.isDir()) {
      appState_->switchBrowsedDirTo(fileInfo.filePath());
    }
  });
}

// TODO: do the same for icons view
void DirListingListWidget::currentChanged(const QModelIndex& current,
                                          const QModelIndex& previous) {
  appState_->switchSelectedPathTo(model_->filePath(current));
}

void DirListingListWidget::focusInEvent(QFocusEvent* event) {
  // Handling a case of nothing being selected on app start. The situation is:
  // - app starts
  // - a dir is selected in the picker component
  // - the user <Tab>s into that dir's listing (this component here)
  // - nothing is selected, while they would rather expect a first time to be selected
  bool isNothingSelected = selectedIndexes().isEmpty();
  bool areItemsAvailable = !model_->rootDirectory().isEmpty(model_->filter());
  if (isNothingSelected && areItemsAvailable) {
    qDebug()
        << "[DirListingListWidget] nothing was selected -> selecting the first item";
    // TODO: pass sort flag here, taken from the model?
    auto firstItemInfo = model_->rootDirectory().entryInfoList(
        model_->filter()).first();
    selectionModel()->select(model_->index(firstItemInfo.filePath()),
                             QItemSelectionModel::SelectionFlag::ClearAndSelect |
                             QItemSelectionModel::SelectionFlag::Rows);
  }

  QTreeView::focusInEvent(event);
}

void DirListingListWidget::slotBrowsedDirChanged() {
  auto dir = appState_->browsedDir();
  // TODO: should I set an entire drive here?
  model_->setRootPath(dir);
  setRootIndex(model_->index(dir));
}

} // namespace qt_file_explorer::widgets
