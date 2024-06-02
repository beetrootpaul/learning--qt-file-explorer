#include "dir_picker_widget.h"

#include <QDir>
#include <QKeyEvent>
#include <QStandardPaths>
#include <QFileSystemModel>

namespace qt_file_explorer::gui {

DirPickerWidget::DirPickerWidget() {
  qDebug() << "+" << this;
}

DirPickerWidget::~DirPickerWidget() {
  qDebug() << "~" << this;

  delete model_;
}

void
DirPickerWidget::init(app_state::AppState* appState) {
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

  auto root = QDir::rootPath();
  model_->setRootPath(root);
  setRootIndex(model_->index(root));

  connect(appState_, &app_state::AppState::signalBrowsedDirChanged, this,
          &DirPickerWidget::slotBrowsedDirChanged);
  connect(this, &DirPickerWidget::clicked, this, &DirPickerWidget::openDir);
}

void DirPickerWidget::keyPressEvent(QKeyEvent* event) {
  if (event->key() == Qt::Key_Return && !selectedIndexes().isEmpty()) {
    openDir(QTreeView::selectedIndexes().first());
  } else {
    QTreeView::keyPressEvent(event);
  }
}

void DirPickerWidget::openDir(const QModelIndex& index) {
  const QFileInfo& fileInfo = model_->fileInfo(index);
  if (fileInfo.isDir()) {
    appState_->switchBrowsedDirTo(
        fileInfo.filePath(), /*originatedFromDirPicker=*/ true);
  }
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
  const auto& modelIndex = model_->index(dir);

  scrollTo(modelIndex,
           QAbstractItemView::ScrollHint::PositionAtCenter);
  setCurrentIndex(modelIndex);
  selectionModel()->select(modelIndex,
                           QItemSelectionModel::SelectionFlag::ClearAndSelect);
}

} // namespace qt_file_explorer::gui
