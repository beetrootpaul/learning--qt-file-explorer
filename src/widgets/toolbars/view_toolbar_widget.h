#ifndef QT_FILE_EXPLORER_WIDGETS_TOOLBARS_VIEW_TOOLBAR_WIDGET_H
#define QT_FILE_EXPLORER_WIDGETS_TOOLBARS_VIEW_TOOLBAR_WIDGET_H

#include <QToolBar>

#include "../../app_state/app_state.h"

namespace qt_file_explorer::widgets {

// TODO: remove this toolbar and make layout reset available through menu

class ViewToolbarWidget : public QToolBar {

Q_OBJECT

public:
  ViewToolbarWidget();
  ~ViewToolbarWidget();

  void init();

signals:
  void signalResetLayoutClicked();

};

} // namespace qt_file_explorer::widgets

#endif //QT_FILE_EXPLORER_WIDGETS_TOOLBARS_VIEW_TOOLBAR_WIDGET_H
