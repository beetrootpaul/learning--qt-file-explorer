#include "directory_picker_widget.h"

#include <QDir>
#include <QStandardPaths>
#include <QFileSystemModel>

namespace qt_file_explorer::widgets {

DirectoryPickerWidget::DirectoryPickerWidget() {
  qDebug() << "+" << this;
}

DirectoryPickerWidget::~DirectoryPickerWidget() {
  qDebug() << "~" << this;
}

// TODO: persist column widths

void DirectoryPickerWidget::init(QSharedPointer<app_state::AppState> appState) {
  appState_ = appState;

  model_ = new QFileSystemModel();
  model_->setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
  setModel(model_);

  // Hide all columns but the first one ("Name")
  for (int i = 1; i < model_->columnCount(); ++i) {
    hideColumn(i);
  }
  setHeaderHidden(true);

  // TODO: test it on Windows: what will be shown? C:\ ? All drives?
  auto rootPath = QDir::rootPath();
  model_->setRootPath(rootPath);
  setRootIndex(model_->index(rootPath));

  connect(appState.data(), &app_state::AppState::signalChanged, this,
          &DirectoryPickerWidget::slotAppStateChanged);

}

// TODO: learn about directoryLoaded signal and if we should wait for it with a selection

void DirectoryPickerWidget::slotAppStateChanged() {
  auto path = appState_->currentPath();
  // TODO: move this to quick actions only?
  collapseAll();
  scrollTo(model_->index(path),
           QAbstractItemView::ScrollHint::PositionAtCenter);
  selectionModel()->select(model_->index(path),
                           QItemSelectionModel::SelectionFlag::ClearAndSelect);
}

} // namespace qt_file_explorer::widgets
