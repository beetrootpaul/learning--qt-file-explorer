#ifndef QT_FILE_EXPLORER_WIDGETS_DOCKS_PREVIEW_DOCK_WIDGET_H
#define QT_FILE_EXPLORER_WIDGETS_DOCKS_PREVIEW_DOCK_WIDGET_H

#include <QDockWidget>

#include "../../app_state/app_state.h"

namespace qt_file_explorer::widgets {

class PreviewDockWidget : public QDockWidget {

public:
  PreviewDockWidget();
  ~PreviewDockWidget();

  void init(const QSharedPointer<app_state::AppState>& appState);

};

} // namespace qt_file_explorer::widgets

#endif //QT_FILE_EXPLORER_WIDGETS_DOCKS_PREVIEW_DOCK_WIDGET_H
