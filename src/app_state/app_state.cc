#include "app_state.h"

#include <QSettings>
#include <QStandardPaths>

#include "../persisted_state/persisted_state_keys.h"
#include "dir_listing_view_type.h"
#include "switch_path_command.h"

namespace qt_file_explorer::app_state {

AppState::AppState() {
  qDebug() << "+" << this;
}

AppState::~AppState() {
  qDebug() << "~" << this;
}

// TODO: persist this between app runs
QString AppState::currentPath() {
  return currentPath_;
}

void AppState::switchPathToHome() {
  switchPathTo(homePath_);
}

void AppState::switchPathToDownloads() {
  switchPathTo(downloadsPath());
}

void AppState::switchPathTo(const QString& path, bool originatedFromDirPicker) {
  undoStack_.push(
      new SwitchPathCommand(this, currentPath_, path, originatedFromDirPicker));
  qDebug() << "[undoStack#count]" << undoStack_.count();
}

void AppState::undoSwitchPath() {
  undoStack_.undo();
  qDebug() << "[undoStack#count]" << undoStack_.count();
}

void AppState::redoSwitchPath() {
  undoStack_.redo();
  qDebug() << "[undoStack#count]" << undoStack_.count();
}

void AppState::setPath(const QString& path, bool originatedFromDirPicker) {
  qDebug() << "Switching path to:" << path;
  currentPath_ = path;
  emit signalPathChanged(originatedFromDirPicker);
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

void AppState::savePersistedState() {
  QSettings settings;

  settings.setValue(persisted_state::PersistedStateKeys::statePath,
                    currentPath_);
  settings.setValue(persisted_state::PersistedStateKeys::stateViewType,
                    (uint) currentDirListingViewType_);
}

void AppState::loadPersistedState() {
  QSettings settings;

  const auto path = settings.value(
      persisted_state::PersistedStateKeys::statePath).toString();
  if (!path.isEmpty()) {
    currentPath_ = path;
  } else {
    currentPath_ = homePath_;
  }

  if (settings.contains(persisted_state::PersistedStateKeys::stateViewType)) {
    currentDirListingViewType_ = (DirListingViewType) settings.value(
        persisted_state::PersistedStateKeys::stateViewType).toUInt();
  } else {
    currentDirListingViewType_ = DirListingViewType::List;
  }
}

QString AppState::downloadsPath() {
  auto locations = QStandardPaths::standardLocations(
      QStandardPaths::DownloadLocation);
  return locations.count() > 0 ? locations.first() : homePath_;
}

} // namespace qt_file_explorer::app_state
