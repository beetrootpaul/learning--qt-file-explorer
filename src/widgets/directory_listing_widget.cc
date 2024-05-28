#include "directory_listing_widget.h"

#include <QFileSystemModel>
#include <QListView>
#include <QStandardPaths>

namespace qt_file_explorer::widgets {

DirectoryListingWidget::DirectoryListingWidget() {
  qDebug() << "+" << this;
}

DirectoryListingWidget::~DirectoryListingWidget() {
  qDebug() << "~" << this;
}

// TODO: handle double-click of files and dirs

// TODO: persist current dir across runs

void
DirectoryListingWidget::init(
    const QSharedPointer<app_state::AppState>& appState) {
  appState_ = appState;

  model_ = new QFileSystemModel();
  model_->setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
  setModel(model_);

  connect(appState.data(), &app_state::AppState::signalPathChanged, this,
          &DirectoryListingWidget::slotPathChanged);
  connect(appState.data(), &app_state::AppState::signalViewTypeChanged, this,
          &DirectoryListingWidget::slotViewTypeChanged);

  connect(this, &QListView::doubleClicked, [=](const QModelIndex& index) {
    const QFileInfo& fileInfo = model_->fileInfo(index);
    if (fileInfo.isDir()) {
      appState_->switchPathTo(fileInfo.filePath());
    }
  });
}

void DirectoryListingWidget::slotPathChanged() {
  auto path = appState_->currentPath();
  // TODO: should I set an entire drive here?
  model_->setRootPath(path);
  setRootIndex(model_->index(path));
}

void DirectoryListingWidget::slotViewTypeChanged() {
  setViewMode(appState_->currentDirListingViewType() ==
              app_state::DirListingViewType::List ? ViewMode::ListMode
                                                  : ViewMode::IconMode);
  // TODO: set it for IconMode only?
  //    QListView::setWrapping(true);

  // TODO: how to make icons nicely aligned to grid, without file names occupying a lot of space
}

} // namespace qt_file_explorer::widgets
