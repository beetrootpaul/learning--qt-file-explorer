#include "directory_listing_widget.h"

#include <QFileSystemModel>
#include <QListView>
#include <QStandardPaths>

namespace qt_file_explorer::widgets {

DirectoryListingWidget::DirectoryListingWidget() {
  model = new QFileSystemModel();
  model->setFilter(QDir::Files);
  QListView::setModel(model);
  setCurrentPath(default_path);
}

void DirectoryListingWidget::setCurrentPath(const QString& path) {
  model->setRootPath(path);
  QListView::setRootIndex(model->index(path));
}

} // namespace qt_file_explorer::widgets
