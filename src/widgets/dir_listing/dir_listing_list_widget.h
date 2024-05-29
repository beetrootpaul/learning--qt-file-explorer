#ifndef QT_FILE_EXPLORER_DIR_LISTING_DIR_LISTING_LIST_WIDGET_H
#define QT_FILE_EXPLORER_DIR_LISTING_DIR_LISTING_LIST_WIDGET_H

#include <QFileSystemModel>
#include <QTreeView>

#include "../../app_state/app_state.h"
#include "dir_listing_shared_model.h"

namespace qt_file_explorer::widgets {

// TODO: share the model with the icons variant, so the selection keeps unchanged? or other benefits?
class DirListingListWidget : public QTreeView {

Q_OBJECT

public:
  DirListingListWidget();
  ~DirListingListWidget();

  void init(const QSharedPointer<DirListingSharedModel>& model_,
            const QSharedPointer<app_state::AppState>& appState);

private:
  QSharedPointer<app_state::AppState> appState_;
  QSharedPointer<DirListingSharedModel> model_;

  void currentChanged(const QModelIndex& current,
                      const QModelIndex& previous) override;

private slots:
  void slotBrowsedDirChanged();

};

} // namespace qt_file_explorer::widgets

#endif //QT_FILE_EXPLORER_DIR_LISTING_DIR_LISTING_LIST_WIDGET_H
