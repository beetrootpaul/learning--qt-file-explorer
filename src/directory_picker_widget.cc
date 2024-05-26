#include "directory_picker_widget.h"

#include <QDir>
#include <QFileSystemModel>
#include <QStandardPaths>

namespace qt_file_explorer::widgets {

DirectoryPickerWidget::DirectoryPickerWidget() {
  model = new QFileSystemModel();
  model->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
  QTreeView::setModel(model);
  setCurrentPath(default_path);
}

void DirectoryPickerWidget::setCurrentPath(const QString& path) {
  model->setRootPath(path);
  QTreeView::setRootIndex(model->index(path));
}

} // namespace qt_file_explorer::widgets
