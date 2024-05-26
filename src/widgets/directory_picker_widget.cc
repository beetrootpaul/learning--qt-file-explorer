#include "directory_picker_widget.h"

#include <iostream>

#include <QDir>
#include <QFileSystemModel>

namespace qt_file_explorer::widgets {

DirectoryPickerWidget::DirectoryPickerWidget() {
  qDebug() << "+" << this;
}

DirectoryPickerWidget::~DirectoryPickerWidget() {
  qDebug() << "~" << this;
}

void DirectoryPickerWidget::init(
    app_state::AppState* appState) {

  auto* model = new QFileSystemModel();
  model->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
  setModel(model);

  connect(appState, &app_state::AppState::changed, [=]() {
    auto path = appState->currentPath();
    // TODO: should I set an entire drive here?
    model->setRootPath(path);
    setRootIndex(model->index(path));
  });
}

} // namespace qt_file_explorer::widgets
