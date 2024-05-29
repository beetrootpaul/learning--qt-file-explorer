#include "dir_picker_widget.h"

#include <QDir>
#include <QStandardPaths>
#include <QFileSystemModel>

namespace qt_file_explorer::widgets {

DirPickerWidget::DirPickerWidget() {
  qDebug() << "+" << this;
}

DirPickerWidget::~DirPickerWidget() {
  qDebug() << "~" << this;

  delete model_;
}

// TODO: persist column widths

void DirPickerWidget::init(
    const QSharedPointer<app_state::AppState>& appState) {
  appState_ = appState;

  model_ = new QFileSystemModel();
  model_->setFilter(QDir::Filter::Dirs | QDir::Filter::NoDotAndDotDot);
  setModel(model_);

  // Hide all columns but the first one ("Name")
  for (int i = 1; i < model_->columnCount(); ++i) {
    hideColumn(i);
  }
  setHeaderHidden(true);

  setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
  setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

  // TODO: test it on Windows: what will be shown? C:\ ? All drives?
  auto root = QDir::rootPath();
  model_->setRootPath(root);
  setRootIndex(model_->index(root));

  connect(appState_.data(), &app_state::AppState::signalBrowsedDirChanged, this,
          &DirPickerWidget::slotBrowsedDirChanged);
  connect(this, &QTreeView::clicked, [=](const QModelIndex& index) {
    const QFileInfo& fileInfo = model_->fileInfo(index);
    if (fileInfo.isDir()) {
      appState_->switchBrowsedDirTo(
          fileInfo.filePath(), /*originatedFromDirPicker=*/
          true);
    }
  });

  // TODO: do I need to do anything about this signal?
  //  connect(model_, &QFileSystemModel::directoryLoaded, [=]() {
  //    qDebug() << "... loaded!";
  //  });
}

void DirPickerWidget::slotBrowsedDirChanged(bool originatedFromDirPicker) {
  // We can either change the dir by clicking it in this QTreeView or with other mean
  // outside the QTreeView. If the change originate from QTreeView, we do not need
  // (nor want) to expand it and select the desired dir, since it is already done,
  // manually, by the user. Especially, we want to avoid a situation where the tree
  // is scrolled to put the selected dir at center, because it is highly confusing
  // for someone who just clicked somewhere in the tree.
  if (originatedFromDirPicker) return;

  auto dir = appState_->browsedDir();

  scrollTo(model_->index(dir),
           QAbstractItemView::ScrollHint::PositionAtCenter);
  selectionModel()->select(model_->index(dir),
                           QItemSelectionModel::SelectionFlag::ClearAndSelect);
}

} // namespace qt_file_explorer::widgets
