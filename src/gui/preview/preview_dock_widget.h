#ifndef QT_FILE_EXPLORER_WIDGETS_DOCKS_PREVIEW_DOCK_WIDGET_H
#define QT_FILE_EXPLORER_WIDGETS_DOCKS_PREVIEW_DOCK_WIDGET_H

#include <QDockWidget>
#include <QObject>

#include "../../app_state/app_state.h"
#include "file_name_preview_widget.h"
#include "image_preview_widget.h"
#include "with_preview_capability.h"

namespace qt_file_explorer::gui {

class PreviewDockWidget : public QDockWidget {

Q_OBJECT

public:
  PreviewDockWidget();
  ~PreviewDockWidget();

  void init(app_state::AppState* appState);

private:
  app_state::AppState* appState_;

  // These gui are ordered from the one specialized the most, to the most generic one.
  // E.g.: image preview goes first, generic file name preview goes second, to be used
  // if the first one cannot preview, because file is not an image.
  QList<QSharedPointer<WithPreviewCapability>> orderedPreviewWidgets_ = QList<QSharedPointer<WithPreviewCapability>>();

private slots:
  void slotUpdatePreview();

};

} // namespace qt_file_explorer::gui

#endif //QT_FILE_EXPLORER_WIDGETS_DOCKS_PREVIEW_DOCK_WIDGET_H
