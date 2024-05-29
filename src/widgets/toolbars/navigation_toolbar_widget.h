#ifndef QT_FILE_EXPLORER_WIDGETS_TOOLBARS_NAVIGATION_TOOLBAR_WIDGET_H
#define QT_FILE_EXPLORER_WIDGETS_TOOLBARS_NAVIGATION_TOOLBAR_WIDGET_H

#include <QToolBar>

#include "../../app_state/app_state.h"

namespace qt_file_explorer::widgets {

class NavigationToolbarWidget : public QToolBar {

Q_OBJECT

public:
  NavigationToolbarWidget();
  ~NavigationToolbarWidget();

  void init(const QSharedPointer<app_state::AppState>& appState);

signals:
  void signalCollapseAllLicked();

};

} // namespace qt_file_explorer::widgets

#endif //QT_FILE_EXPLORER_WIDGETS_TOOLBARS_NAVIGATION_TOOLBAR_WIDGET_H
