#ifndef QT_FILE_EXPLORER_WIDGETS_DIR_LISTING_SHARED_MODEL_H
#define QT_FILE_EXPLORER_WIDGETS_DIR_LISTING_SHARED_MODEL_H

#include <QFileSystemModel>

namespace qt_file_explorer::widgets {

class DirListingSharedModel : public QFileSystemModel {

public:
  DirListingSharedModel() {
    setObjectName("DirListingSharedModel");
    qDebug() << "+" << this;
    setFilter(QDir::Filter::AllEntries | QDir::Filter::NoDotAndDotDot);
  }

  ~DirListingSharedModel() {
    qDebug() << "~" << this;
  }

};

} // namespace qt_file_explorer::widgets

#endif //QT_FILE_EXPLORER_WIDGETS_DIR_LISTING_SHARED_MODEL_H
