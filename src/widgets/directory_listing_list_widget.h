#ifndef QT_FILE_EXPLORER_DIRECTORY_LISTING_LIST_WIDGET_H
#define QT_FILE_EXPLORER_DIRECTORY_LISTING_LIST_WIDGET_H

#import <QFileSystemModel>
#import <QTreeView>

#include "../app_state/app_state.h"

namespace qt_file_explorer::widgets {

// TODO: share the model with the icons variant, so the selection keeps unchanged? or other benefits?
class DirectoryListingListWidget : public QTreeView {

Q_OBJECT

public:
  DirectoryListingListWidget();
  ~DirectoryListingListWidget();

  void init(const QSharedPointer<app_state::AppState>& appState);

private:
  QSharedPointer<app_state::AppState> appState_;
  QFileSystemModel* model_ = nullptr;

private slots:
  void slotPathChanged();

};

} // namespace qt_file_explorer::widgets

#endif //QT_FILE_EXPLORER_DIRECTORY_LISTING_LIST_WIDGET_H
