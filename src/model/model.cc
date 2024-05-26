#include "model.h"

#include <QStandardPaths>

#include "dir_listing_view_type.h"

namespace qt_file_explorer::model {

Model::Model() {
  current_path_ = downloadsPath();
  dir_listing_view_type_ = DirListingViewType::List;
}

QString Model::currentPath() {
  return current_path_;
}

void Model::switchPathToDownloads() {
  current_path_ = downloadsPath();
}

DirListingViewType Model::currentDirListingViewType() {
  return dir_listing_view_type_;
}

void Model::setDirListingViewType(DirListingViewType viewType) {
  dir_listing_view_type_ = viewType;
}

QString Model::downloadsPath() {
  auto locations = QStandardPaths::standardLocations(
      QStandardPaths::DownloadLocation);
  return locations.count() > 0 ? locations.first() : fallback_path_;
}

} // namespace qt_file_explorer::model
