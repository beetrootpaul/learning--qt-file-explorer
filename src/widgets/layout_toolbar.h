#ifndef QT_FILE_EXPLORER_WIDGETS_LAYOUT_TOOLBAR_H
#define QT_FILE_EXPLORER_WIDGETS_LAYOUT_TOOLBAR_H

#include <QToolBar>

#include "../app_state/app_state.h"

namespace qt_file_explorer::widgets {

class LayoutToolbar : public QToolBar {

Q_OBJECT

public:
  LayoutToolbar();
  ~LayoutToolbar();

  void init();

signals:
  void signalResetLayoutClicked();

};

} // namespace qt_file_explorer::widgets

#endif //QT_FILE_EXPLORER_WIDGETS_LAYOUT_TOOLBAR_H
