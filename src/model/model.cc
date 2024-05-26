#include "model.h"

#include <QDir>
#include <QStandardPaths>

#include "dir_listing_view_type.h"

namespace qt_file_explorer::model {

QString Model::currentPath() {
  auto locations = QStandardPaths::standardLocations(
      QStandardPaths::DownloadLocation);
  return locations.count() > 0
         ? locations.first()
         : QDir::homePath();
}

DirListingViewType Model::currentDirListingViewType() {
  return dir_listing_view_type_;
}

void Model::setDirListingViewType(DirListingViewType viewType) {
  dir_listing_view_type_ = viewType;
}

} // namespace qt_file_explorer::model
