#include <QDir>
#include <QStandardPaths>
#include "model.h"

namespace qt_file_explorer::model {

QString Model::currentPath() {
  auto locations = QStandardPaths::standardLocations(
      QStandardPaths::DownloadLocation);
  return locations.count() > 0
         ? locations.first()
         : QDir::homePath();
}

} // namespace qt_file_explorer::model
