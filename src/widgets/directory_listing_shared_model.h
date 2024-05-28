#ifndef QT_FILE_EXPLORER_WIDGETS_DIRECTORY_LISTING_SHARED_MODEL_H
#define QT_FILE_EXPLORER_WIDGETS_DIRECTORY_LISTING_SHARED_MODEL_H

#include <QFileSystemModel>

namespace qt_file_explorer::widgets {

class DirectoryListingSharedModel : public QFileSystemModel {

public:
  DirectoryListingSharedModel() {
    setObjectName("DirectoryListingSharedModel");
    qDebug() << "+" << this;
    setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
  }

  ~DirectoryListingSharedModel() {
    qDebug() << "~" << this;
  }

};

} // namespace qt_file_explorer::widgets

#endif //QT_FILE_EXPLORER_WIDGETS_DIRECTORY_LISTING_SHARED_MODEL_H
