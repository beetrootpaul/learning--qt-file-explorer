#include "dir_listing_list_widget.h"

#include <QFileSystemModel>
#include <QStandardPaths>

namespace qt_file_explorer::widgets {

DirListingListWidget::DirListingListWidget() {
  qDebug() << "+" << this;
}

DirListingListWidget::~DirListingListWidget() {
  qDebug() << "~" << this;
}

// TODO: handle double-click of files and dirs

// TODO: persist current dir across runs

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

  connect(appState.data(), &app_state::AppState::signalPathChanged, this,
          &DirListingListWidget::slotPathChanged);

  connect(this, &QTreeView::doubleClicked, [=](const QModelIndex& index) {
    const QFileInfo& fileInfo = model_->fileInfo(index);
    if (fileInfo.isDir()) {
      appState_->switchPathTo(fileInfo.filePath());
    }
  });
}

void DirListingListWidget::slotPathChanged() {
  auto path = appState_->currentPath();
  // TODO: should I set an entire drive here?
  model_->setRootPath(path);
  setRootIndex(model_->index(path));
}

} // namespace qt_file_explorer::widgets
