#ifndef QT_FILE_EXPLORER_DIRECTORY_LISTING_ICONS_WIDGET_H
#define QT_FILE_EXPLORER_DIRECTORY_LISTING_ICONS_WIDGET_H

#import <QFileSystemModel>
#import <QListView>

#include "../app_state/app_state.h"

namespace qt_file_explorer::widgets {

// TODO: share the model with the list variant, so the selection keeps unchanged? or other benefits?
class DirectoryListingIconsWidget : public QListView {

Q_OBJECT

public:
  DirectoryListingIconsWidget();
  ~DirectoryListingIconsWidget();

  void init(const QSharedPointer<app_state::AppState>& appState);

private:
  QSharedPointer<app_state::AppState> appState_;
  QFileSystemModel* model_ = nullptr;

private slots:
  void slotPathChanged();

};

} // namespace qt_file_explorer::widgets

#endif //QT_FILE_EXPLORER_DIRECTORY_LISTING_ICONS_WIDGET_H
