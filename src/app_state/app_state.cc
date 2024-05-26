#include "app_state.h"

#include <QSettings>
#include <QStandardPaths>

#include "dir_listing_view_type.h"

namespace qt_file_explorer::app_state {

AppState::AppState() {
  currentPath_ = homePath_;
  currentDirListingViewType_ = DirListingViewType::List;
}

// TODO: persist this between app runs
QString AppState::currentPath() {
  return currentPath_;
}

void AppState::switchPathToHome() {
  currentPath_ = homePath_;
  emit changed();
}

void AppState::switchPathToDownloads() {
  currentPath_ = downloadsPath();
  emit changed();
}

DirListingViewType AppState::currentDirListingViewType() {
  return currentDirListingViewType_;
}

// TODO: persist this between app runs
void AppState::toggleDirListingViewType() {
  currentDirListingViewType_ =
      currentDirListingViewType_ == DirListingViewType::List
      ? DirListingViewType::Icons : DirListingViewType::List;
  emit changed();
}

void AppState::savePersistedState() {
  QSettings settings;

  settings.setValue("v3/state/path", currentPath_);
}

void AppState::loadPersistedState() {
  QSettings settings;

  const auto path = settings.value("v3/state/path").toString();
  if (!path.isEmpty()) {
    currentPath_ = path;
  } else {
    currentPath_ = homePath_;
  }
}

QString AppState::downloadsPath() {
  auto locations = QStandardPaths::standardLocations(
      QStandardPaths::DownloadLocation);
  return locations.count() > 0 ? locations.first() : homePath_;
}

} // namespace qt_file_explorer::app_state
