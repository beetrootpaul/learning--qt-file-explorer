#include "dir_listing_icons_widget.h"

#include <QFileSystemModel>
#include <QLayout>
#include <QListView>
#include <QStandardPaths>

namespace qt_file_explorer::widgets {

// TODO: set it for IconMode only?
//    QListView::setWrapping(true);

// TODO: how to make icons nicely aligned to grid, without file names occupying a lot of space

DirListingIconsWidget::DirListingIconsWidget() {
  qDebug() << "+" << this;
}

DirListingIconsWidget::~DirListingIconsWidget() {
  qDebug() << "~" << this;
}

// TODO: handle double-click of files and dirs

// TODO: persist current dir across runs

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
  setGridSize(QSize(72, 56));
  setResizeMode(QListView::Adjust);

  connect(appState.data(), &app_state::AppState::signalPathChanged, this,
          &DirListingIconsWidget::slotPathChanged);

  connect(this, &DirListingIconsWidget::doubleClicked,
          [=](const QModelIndex& index) {
            const QFileInfo& fileInfo = model_->fileInfo(index);
            if (fileInfo.isDir()) {
              appState_->switchPathTo(fileInfo.filePath());
            }
          });
}

void DirListingIconsWidget::slotPathChanged() {
  auto path = appState_->currentPath();
  // TODO: should I set an entire drive here?
  model_->setRootPath(path);
  setRootIndex(model_->index(path));
}

} // namespace qt_file_explorer::widgets
