#include "directory_listing_widget.h"

#include <QFileSystemModel>
#include <QListView>
#include <QStandardPaths>

namespace qt_file_explorer::widgets {

DirectoryListingWidget::DirectoryListingWidget() {
  file_system_model_ = new QFileSystemModel();
  file_system_model_->setFilter(QDir::Files);
  QListView::setModel(file_system_model_);
}

void DirectoryListingWidget::setModel(model::Model* model) {
  model_ = model;

  QObject::connect(model_, &model::Model::changed, [=]() {
    auto path = model_->currentPath();
    file_system_model_->setRootPath(path);
    QListView::setRootIndex(file_system_model_->index(path));

    auto viewType = model_->currentDirListingViewType();
    QListView::setViewMode(
        viewType == model::DirListingViewType::List ? ViewMode::ListMode
                                                    : ViewMode::IconMode);
    // TODO: set it for IconMode only?
    QListView::setWrapping(true);
    // TODO: how to make icons nicely aligned to grid, without file names occupying a lot of space
  });
}

} // namespace qt_file_explorer::widgets
