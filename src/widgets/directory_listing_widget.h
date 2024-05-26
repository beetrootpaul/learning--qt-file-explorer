#ifndef QT_FILE_EXPLORER_DIRECTORY_LISTING_WIDGET_H
#define QT_FILE_EXPLORER_DIRECTORY_LISTING_WIDGET_H

#import <QFileSystemModel>
#import <QListView>

#include "../app_state/app_state.h"

namespace qt_file_explorer::widgets {

// TODO: change to QTableView, but support icons from QListView as well
class DirectoryListingWidget : public QListView {

Q_OBJECT

public:
  DirectoryListingWidget();
  ~DirectoryListingWidget();

  void init(app_state::AppState* appState);

};

} // namespace qt_file_explorer::widgets

#endif //QT_FILE_EXPLORER_DIRECTORY_LISTING_WIDGET_H
