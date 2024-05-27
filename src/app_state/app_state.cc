#include "app_state.h"

#include <QSettings>
#include <QStandardPaths>

#include "dir_listing_view_type.h"

namespace qt_file_explorer::app_state {

AppState::AppState() {
  qDebug() << "+" << this;

  currentPath_ = homePath_;
  currentDirListingViewType_ = DirListingViewType::List;
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

// TODO: sometimes (quite often) the path switch makes the entire tree go back to root… is it some race condition with a dir being loaded?
void AppState::switchPathTo(const QString& path, bool originatedFromDirPicker) {
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

  // TODO: extract keys
  settings.setValue("v3/state/path", currentPath_);
  settings.setValue("v3/state/view_type", (uint) currentDirListingViewType_);
}

void AppState::loadPersistedState() {
  QSettings settings;

  const auto path = settings.value("v3/state/path").toString();
  if (!path.isEmpty()) {
    currentPath_ = path;
  } else {
    currentPath_ = homePath_;
  }

  if (settings.contains("v3/state/view_type")) {
    currentDirListingViewType_ = (DirListingViewType) settings.value(
        "v3/state/view_type").toUInt();
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
