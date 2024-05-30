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

} // namespace qt_file_explorer::gui
