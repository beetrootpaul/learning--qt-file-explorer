#ifndef QT_FILE_EXPLORER_DIR_LISTING_DIR_LISTING_LIST_WIDGET_H
#define QT_FILE_EXPLORER_DIR_LISTING_DIR_LISTING_LIST_WIDGET_H

#include <QFileSystemModel>
#include <QTreeView>

#include "../../app_state/app_state.h"
#include "../../persisted_state/with_persisted_state.h"
#include "dir_listing_shared_model.h"

namespace qt_file_explorer::gui {

class DirListingListWidget
    : public QTreeView, public persisted_state::WithPersistedState {

Q_OBJECT

public:
  DirListingListWidget();
  ~DirListingListWidget();

  void init(const QSharedPointer<DirListingSharedModel>& model_,
            app_state::AppState* appState);

  void savePersistedState() override;
  void loadPersistedState() override;

private:
  app_state::AppState* appState_;
  QSharedPointer<DirListingSharedModel> model_;

  void currentChanged(const QModelIndex& current,
                      const QModelIndex& previous) override;
  void focusInEvent(QFocusEvent* event) override;

private slots:
  void slotBrowsedDirChanged();

};

} // namespace qt_file_explorer::gui

#endif //QT_FILE_EXPLORER_DIR_LISTING_DIR_LISTING_LIST_WIDGET_H
