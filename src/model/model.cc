#include "model.h"

#include <QStandardPaths>

#include "dir_listing_view_type.h"

namespace qt_file_explorer::model {

Model::Model() {
  current_path_ = home_path_;
  dir_listing_view_type_ = DirListingViewType::List;
}

QString Model::currentPath() {
  return current_path_;
}

void Model::switchPathToHome() {
  current_path_ = home_path_;
  emit changed();
}

void Model::switchPathToDownloads() {
  current_path_ = downloadsPath();
  emit changed();
}

DirListingViewType Model::currentDirListingViewType() {
  return dir_listing_view_type_;
}

// TODO: persist this between app runs
void Model::setDirListingViewType(DirListingViewType viewType) {
  dir_listing_view_type_ = viewType;
  emit changed();
}

QString Model::downloadsPath() {
  auto locations = QStandardPaths::standardLocations(
      QStandardPaths::DownloadLocation);
  return locations.count() > 0 ? locations.first() : home_path_;
}

} // namespace qt_file_explorer::model
