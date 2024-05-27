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

  setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
  setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

  // TODO: test it on Windows: what will be shown? C:\ ? All drives?
  auto rootPath = QDir::rootPath();
  model_->setRootPath(rootPath);
  setRootIndex(model_->index(rootPath));

  connect(appState.data(), &app_state::AppState::signalPathChanged, this,
          &DirectoryPickerWidget::slotPathChanged);

  // TODO: do I need to do anything about this signal?
  //  connect(model_, &QFileSystemModel::directoryLoaded, [=]() {
  //    qDebug() << "... loaded!";
  //  });
}

// TODO: learn about directoryLoaded signal and if we should wait for it with a selection

void DirectoryPickerWidget::slotPathChanged(bool originatedFromDirPicker) {
  if (originatedFromDirPicker) return;

  auto path = appState_->currentPath();

  scrollTo(model_->index(path),
           QAbstractItemView::ScrollHint::PositionAtCenter);
  selectionModel()->select(model_->index(path),
                           QItemSelectionModel::SelectionFlag::ClearAndSelect);
}

// This slot will be called every time user selects a folder *by hand*.
// In other words, this won't happen for selections made through path
// switching initiated programmatically, outside the QTreeView.
void DirectoryPickerWidget::currentChanged(const QModelIndex& current,
                                           const QModelIndex& previous) {
  auto newPath = model_->filePath(current);
  appState_->switchPathTo(newPath, /*originatedFromDirPicker=*/true);
}

} // namespace qt_file_explorer::widgets
