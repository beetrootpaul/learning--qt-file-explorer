#include "directory_listing_widget.h"

#include <QFileSystemModel>
#include <QListView>
#include <QStandardPaths>

namespace qt_file_explorer::widgets {

DirectoryListingWidget::DirectoryListingWidget() {
  model_ = new QFileSystemModel();
  model_->setFilter(QDir::Files);
  QListView::setModel(model_);
  setCurrentPath(default_path_);
}

void DirectoryListingWidget::setCurrentPath(const QString& path) {
  model_->setRootPath(path);
  QListView::setRootIndex(model_->index(path));
}

} // namespace qt_file_explorer::widgets
