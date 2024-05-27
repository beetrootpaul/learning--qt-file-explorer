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

void DirectoryListingWidget::init(app_state::AppState* appState) {
  appState_ = appState;

  model_ = new QFileSystemModel();
  model_->setFilter(QDir::Files);
  setModel(model_);

  connect(appState, &app_state::AppState::signalChanged, this,
          &DirectoryListingWidget::slotAppStateChanged);
}

void DirectoryListingWidget::slotAppStateChanged() {
  auto path = appState_->currentPath();
  // TODO: should I set an entire drive here?
  model_->setRootPath(path);
  setRootIndex(model_->index(path));

  setViewMode(appState_->currentDirListingViewType() ==
              app_state::DirListingViewType::List ? ViewMode::ListMode
                                                  : ViewMode::IconMode);
  // TODO: set it for IconMode only?
  //    QListView::setWrapping(true);
  
  // TODO: how to make icons nicely aligned to grid, without file names occupying a lot of space
}

} // namespace qt_file_explorer::widgets
