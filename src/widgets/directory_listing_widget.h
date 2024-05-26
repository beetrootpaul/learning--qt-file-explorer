#ifndef QT_FILE_EXPLORER_SRC_DIRECTORY_LISTING_WIDGET_H
#define QT_FILE_EXPLORER_SRC_DIRECTORY_LISTING_WIDGET_H

#import <QFileSystemModel>
#import <QListView>

namespace qt_file_explorer::widgets {

class DirectoryListingWidget : public QListView {

public:
  DirectoryListingWidget();
  void setCurrentPath(const QString& path);

private:
  const QString default_path_ = QDir::homePath();
  QFileSystemModel* model_;

};

} // namespace qt_file_explorer::widgets

#endif //QT_FILE_EXPLORER_SRC_DIRECTORY_LISTING_WIDGET_H
