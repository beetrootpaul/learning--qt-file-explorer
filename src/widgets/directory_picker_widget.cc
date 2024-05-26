#include "directory_picker_widget.h"

#include <iostream>

#include <QDir>
#include <QFileSystemModel>
#include <QStandardPaths>

namespace qt_file_explorer::widgets {

// TODO: model_ not initialized in constructor :-(
DirectoryPickerWidget::DirectoryPickerWidget() {
  file_system_model_ = new QFileSystemModel();
  file_system_model_->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
  QTreeView::setModel(file_system_model_);
}

void DirectoryPickerWidget::setModel(model::Model* model) {
  model_ = model;

  QObject::connect(model_, &model::Model::changed, [=]() {
    const QString& path = model_->currentPath();
    file_system_model_->setRootPath(path);
    QTreeView::setRootIndex(file_system_model_->index(path));
  });
}

} // namespace qt_file_explorer::widgets
