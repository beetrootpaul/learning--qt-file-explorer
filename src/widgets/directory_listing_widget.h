#ifndef QT_FILE_EXPLORER_SRC_DIRECTORY_LISTING_WIDGET_H
#define QT_FILE_EXPLORER_SRC_DIRECTORY_LISTING_WIDGET_H

#import <QFileSystemModel>
#import <QListView>

#include "../model/model.h"

namespace qt_file_explorer::widgets {

class DirectoryListingWidget : public QListView {

public:
  DirectoryListingWidget();
  void setModel(model::Model* model);

private:
  model::Model* model_;
  QFileSystemModel* file_system_model_;

};

} // namespace qt_file_explorer::widgets

#endif //QT_FILE_EXPLORER_SRC_DIRECTORY_LISTING_WIDGET_H
