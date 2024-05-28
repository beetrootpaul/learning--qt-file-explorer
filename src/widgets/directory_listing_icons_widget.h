#ifndef QT_FILE_EXPLORER_DIRECTORY_LISTING_ICONS_WIDGET_H
#define QT_FILE_EXPLORER_DIRECTORY_LISTING_ICONS_WIDGET_H

#import <QFileSystemModel>
#import <QListView>

#include "../app_state/app_state.h"
#include "directory_listing_shared_model.h"

namespace qt_file_explorer::widgets {

class DirectoryListingIconsWidget : public QListView {

Q_OBJECT

public:
  DirectoryListingIconsWidget();
  ~DirectoryListingIconsWidget();

  void init(const QSharedPointer<DirectoryListingSharedModel>& model_,
            const QSharedPointer<app_state::AppState>& appState);

private:
  QSharedPointer<app_state::AppState> appState_;
  QSharedPointer<DirectoryListingSharedModel> model_;

private slots:
  void slotPathChanged();

};

} // namespace qt_file_explorer::widgets

#endif //QT_FILE_EXPLORER_DIRECTORY_LISTING_ICONS_WIDGET_H
