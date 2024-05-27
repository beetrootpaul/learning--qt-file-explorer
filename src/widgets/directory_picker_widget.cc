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

void DirectoryPickerWidget::init(QSharedPointer<app_state::AppState> appState) {
  appState_ = appState;

  model_ = new QFileSystemModel();
  model_->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
  setModel(model_);

  connect(appState.data(), &app_state::AppState::signalChanged, this,
          &DirectoryPickerWidget::slotAppStateChanged);
}

void DirectoryPickerWidget::slotAppStateChanged() {
  auto path = appState_->currentPath();
  // TODO: should I set an entire drive here?
  model_->setRootPath(path);
  setRootIndex(model_->index(path));
}

} // namespace qt_file_explorer::widgets
