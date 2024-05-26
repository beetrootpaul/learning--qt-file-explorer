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

void DirectoryListingWidget::init(
    app_state::AppState* appState) {
  auto* model = new QFileSystemModel();
  model->setFilter(QDir::Files);
  setModel(model);

  connect(appState, &app_state::AppState::changed, [=]() {
    auto path = appState->currentPath();
    // TODO: should I set an entire drive here?
    model->setRootPath(path);
    setRootIndex(model->index(path));

    setViewMode(appState->currentDirListingViewType() ==
                app_state::DirListingViewType::List ? ViewMode::ListMode
                                                    : ViewMode::IconMode);
    // TODO: set it for IconMode only?
    //    QListView::setWrapping(true);
    // TODO: how to make icons nicely aligned to grid, without file names occupying a lot of space
  });
}

} // namespace qt_file_explorer::widgets
