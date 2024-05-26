#include "directory_picker_widget.h"

#include <QDir>
#include <QFileSystemModel>
#include <QStandardPaths>

namespace qt_file_explorer::widgets {

DirectoryPickerWidget::DirectoryPickerWidget() {
  model_ = new QFileSystemModel();
  model_->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
  QTreeView::setModel(model_);
  setCurrentPath(default_path_);
}

void DirectoryPickerWidget::setCurrentPath(const QString& path) {
  model_->setRootPath(path);
  QTreeView::setRootIndex(model_->index(path));
}

} // namespace qt_file_explorer::widgets
