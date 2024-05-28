#include "directory_listing_icons_widget.h"

#include <QFileSystemModel>
#include <QLayout>
#include <QListView>
#include <QStandardPaths>

namespace qt_file_explorer::widgets {

// TODO: set it for IconMode only?
//    QListView::setWrapping(true);

// TODO: how to make icons nicely aligned to grid, without file names occupying a lot of space

DirectoryListingIconsWidget::DirectoryListingIconsWidget() {
  qDebug() << "+" << this;
}

DirectoryListingIconsWidget::~DirectoryListingIconsWidget() {
  qDebug() << "~" << this;
}

// TODO: handle double-click of files and dirs

// TODO: persist current dir across runs

void
DirectoryListingIconsWidget::init(
    const QSharedPointer<DirectoryListingSharedModel>& model,
    const QSharedPointer<app_state::AppState>& appState) {
  model_ = model;
  appState_ = appState;

  setModel(model_.get());

  setViewMode(ViewMode::IconMode);
  setWrapping(true);
  setWordWrap(false);
  setGridSize(QSize(72, 56));
  setResizeMode(QListView::Adjust);

  connect(appState.data(), &app_state::AppState::signalPathChanged, this,
          &DirectoryListingIconsWidget::slotPathChanged);

  connect(this, &DirectoryListingIconsWidget::doubleClicked,
          [=](const QModelIndex& index) {
            const QFileInfo& fileInfo = model_->fileInfo(index);
            if (fileInfo.isDir()) {
              appState_->switchPathTo(fileInfo.filePath());
            }
          });
}

void DirectoryListingIconsWidget::slotPathChanged() {
  auto path = appState_->currentPath();
  // TODO: should I set an entire drive here?
  model_->setRootPath(path);
  setRootIndex(model_->index(path));
}

} // namespace qt_file_explorer::widgets
