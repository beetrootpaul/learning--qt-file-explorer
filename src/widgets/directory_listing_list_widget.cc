#include "directory_listing_list_widget.h"

#include <QFileSystemModel>
#include <QStandardPaths>

namespace qt_file_explorer::widgets {

DirectoryListingListWidget::DirectoryListingListWidget() {
  qDebug() << "+" << this;
}

DirectoryListingListWidget::~DirectoryListingListWidget() {
  qDebug() << "~" << this;
}

// TODO: handle double-click of files and dirs

// TODO: persist current dir across runs

void
DirectoryListingListWidget::init(
    const QSharedPointer<DirectoryListingSharedModel>& model,
    const QSharedPointer<app_state::AppState>& appState) {
  model_ = model;
  appState_ = appState;

  setModel(model_.get());

  // Make this tree look like a regular flat list
  setRootIsDecorated(false);
  setItemsExpandable(false);

  connect(appState.data(), &app_state::AppState::signalPathChanged, this,
          &DirectoryListingListWidget::slotPathChanged);

  connect(this, &QTreeView::doubleClicked, [=](const QModelIndex& index) {
    const QFileInfo& fileInfo = model_->fileInfo(index);
    if (fileInfo.isDir()) {
      appState_->switchPathTo(fileInfo.filePath());
    }
  });
}

void DirectoryListingListWidget::slotPathChanged() {
  auto path = appState_->currentPath();
  // TODO: should I set an entire drive here?
  model_->setRootPath(path);
  setRootIndex(model_->index(path));
}

} // namespace qt_file_explorer::widgets
