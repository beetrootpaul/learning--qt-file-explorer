#ifndef QT_FILE_EXPLORER_DIR_LISTING_DIR_LISTING_ICONS_WIDGET_H
#define QT_FILE_EXPLORER_DIR_LISTING_DIR_LISTING_ICONS_WIDGET_H

#include <QFileSystemModel>
#include <QListView>

#include "../../app_state/app_state.h"
#include "dir_listing_shared_model.h"

namespace qt_file_explorer::gui {

class DirListingIconsWidget : public QListView {

Q_OBJECT

public:
  DirListingIconsWidget();
  ~DirListingIconsWidget();

  void init(const QSharedPointer<DirListingSharedModel>& model_,
            app_state::AppState* appState);

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

#endif //QT_FILE_EXPLORER_DIR_LISTING_DIR_LISTING_ICONS_WIDGET_H
