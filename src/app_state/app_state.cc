#include "app_state.h"

#include <QSettings>
#include <QStandardPaths>

#include "../persisted_state/persisted_state_keys.h"
#include "dir_listing_view_type.h"
#include "switch_dir_command.h"

namespace qt_file_explorer::app_state {

AppState::AppState() {
  qDebug() << "+" << this;
}

AppState::~AppState() {
  qDebug() << "~" << this;
}

QString AppState::browsedDir() {
  return browsedDir_;
}

void AppState::switchBrowsedDirToHome() {
  switchBrowsedDirTo(homeDir_);
}

void AppState::switchBrowsedDirToDownloads() {
  switchBrowsedDirTo(downloadsDir());
}

void
AppState::switchBrowsedDirTo(const QString& dir, bool originatedFromDirPicker) {
  if (dir.trimmed().isEmpty()) return;

  // Do nothing if the to-be browsed dir is the current one.
  if (browsedDir_ == dir) return;

  undoStack_.push(
      new SwitchDirCommand(this, browsedDir_, dir, originatedFromDirPicker));
  qDebug() << "[undoStack#index/count]" << undoStack_.index() << "/"
           << undoStack_.count();

  // We need a separate signal here, because:
  // - `signalBrowsedDirChanged` is emitted from within `SwitchDirCommand`,
  //   which is before `undoStack_` gets updated with an info there is
  //   1 new command on it.
  // - `signalBrowsedDirHistoryUpdated` here is emitted after `undoStack_`
  //   has knowledge about that command being already added.
  emit signalBrowsedDirHistoryUpdated();
}

bool AppState::canUndoSwitchBrowsedDir() {
  return undoStack_.canUndo();
}

bool AppState::canRedoSwitchBrowsedDir() {
  return undoStack_.canRedo();
}

void AppState::undoSwitchBrowsedDir() {
  undoStack_.undo();
  qDebug() << "[undoStack#index/count]" << undoStack_.index() << "/"
           << undoStack_.count();
  emit signalBrowsedDirHistoryUpdated();
}

void AppState::redoSwitchBrowsedDir() {
  undoStack_.redo();
  qDebug() << "[undoStack#index/count]" << undoStack_.index() << "/"
           << undoStack_.count();
  emit signalBrowsedDirHistoryUpdated();
}

void AppState::setBrowsedDir(const QString& dir, bool originatedFromDirPicker) {
  qDebug() << "Switching browsed dir to:" << dir;
  browsedDir_ = dir;
  emit signalBrowsedDirChanged(originatedFromDirPicker);
}

DirListingViewType AppState::currentDirListingViewType() {
  return currentDirListingViewType_;
}

void AppState::toggleDirListingViewType() {
  currentDirListingViewType_ =
      currentDirListingViewType_ == DirListingViewType::List
      ? DirListingViewType::Icons : DirListingViewType::List;
  emit signalViewTypeChanged();
}

QString AppState::selectedPath() {
  return selectedPath_;
}

void AppState::switchSelectedPathTo(const QString& path) {
  if (path.trimmed().isEmpty()) return;

  qDebug() << "Switching selected path to:" << path;
  selectedPath_ = path;
  emit signalSelectedPathChanged();
}

bool AppState::isPreviewVisible() {
  return isPreviewVisible_;
}

void AppState::togglePreviewVisible() {
  isPreviewVisible_ = !isPreviewVisible_;
  emit signalPreviewVisibleChanged();
}

void AppState::savePersistedState() {
  QSettings settings;

  settings.setValue(persisted_state::PersistedStateKeys::browsedDir,
                    browsedDir_);
  settings.setValue(persisted_state::PersistedStateKeys::listingViewType,
                    (uint) currentDirListingViewType_);
  settings.setValue(persisted_state::PersistedStateKeys::previewVisible,
                    isPreviewVisible_);
}

void AppState::loadPersistedState() {
  QSettings settings;

  const auto dir = settings.value(
      persisted_state::PersistedStateKeys::browsedDir).toString();
  if (!dir.isEmpty()) {
    browsedDir_ = dir;
  } else {
    browsedDir_ = homeDir_;
  }

  if (settings.contains(persisted_state::PersistedStateKeys::listingViewType)) {
    currentDirListingViewType_ = (DirListingViewType) settings.value(
        persisted_state::PersistedStateKeys::listingViewType).toUInt();
  } else {
    currentDirListingViewType_ = DirListingViewType::List;
  }

  if (settings.contains(persisted_state::PersistedStateKeys::previewVisible)) {
    isPreviewVisible_ = settings.value(
        persisted_state::PersistedStateKeys::previewVisible).toBool();
  } else {
    isPreviewVisible_ = false;
  }
}

QString AppState::downloadsDir() {
  auto locations = QStandardPaths::standardLocations(
      QStandardPaths::DownloadLocation);
  return locations.count() > 0 ? locations.first() : homeDir_;
}

} // namespace qt_file_explorer::app_state
