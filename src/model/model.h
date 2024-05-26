#ifndef QT_FILE_EXPLORER_SRC_MODEL_H
#define QT_FILE_EXPLORER_SRC_MODEL_H

#include <QDir>
#include <QObject>
#include <QString>

#include "dir_listing_view_type.h"

namespace qt_file_explorer::model {

class Model : public QObject {

Q_OBJECT

public:
  Model();

  QString currentPath();
  void switchPathToDownloads();

  DirListingViewType currentDirListingViewType();
  void setDirListingViewType(DirListingViewType viewType);

signals:
  void changed();

private:
  const QString fallback_path_ = QDir::homePath();
  QString current_path_;
  DirListingViewType dir_listing_view_type_;

  QString downloadsPath();

};

} // namespace qt_file_explorer::model

#endif //QT_FILE_EXPLORER_SRC_MODEL_H
