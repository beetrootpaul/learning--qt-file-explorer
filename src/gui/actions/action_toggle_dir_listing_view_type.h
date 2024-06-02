#ifndef QT_FILE_EXPLORER_GUI_ACTIONS_ACTION_TOGGLE_DIR_LISTING_VIEW_TYPE_H
#define QT_FILE_EXPLORER_GUI_ACTIONS_ACTION_TOGGLE_DIR_LISTING_VIEW_TYPE_H

#include <QAction>
#include <QObject>

#include "../../app_state/app_state.h"

namespace qt_file_explorer::gui {

class ActionToggleDirListingViewType : public QAction {

Q_OBJECT

public:
  ActionToggleDirListingViewType(QObject* parent,
                                 app_state::AppState* appState);
  ~ActionToggleDirListingViewType();

private:
  app_state::AppState* appState_;

private slots:
  void perform();

};

} // namespace qt_file_explorer::gui

#endif //QT_FILE_EXPLORER_GUI_ACTIONS_ACTION_TOGGLE_DIR_LISTING_VIEW_TYPE_H
