#ifndef QT_FILE_EXPLORER_WIDGETS_PREVIEW_IMAGE_PREVIEW_WIDGET_H
#define QT_FILE_EXPLORER_WIDGETS_PREVIEW_IMAGE_PREVIEW_WIDGET_H

#include <QLabel>
#include <QObject>

#include "../../app_state/app_state.h"

namespace qt_file_explorer {

class ImagePreviewWidget : public QLabel {

Q_OBJECT

public:
  ImagePreviewWidget();
  ~ImagePreviewWidget();

  void init(const QSharedPointer<app_state::AppState>& appState);

private:
  QPixmap srcPixmap_;
  QPixmap currPixmap_;

  void paintEvent(QPaintEvent* event) override;

};

} // namespace qt_file_explorer

#endif //QT_FILE_EXPLORER_WIDGETS_PREVIEW_IMAGE_PREVIEW_WIDGET_H
