#include "preview_dock_widget.h"

#include "image_preview_widget.h"

namespace qt_file_explorer::widgets {

PreviewDockWidget::PreviewDockWidget() {
  setObjectName("PreviewDockWidget");
  qDebug() << "+" << this;
}

PreviewDockWidget::~PreviewDockWidget() {
  qDebug() << "~" << this;
}

void
PreviewDockWidget::init(const QSharedPointer<app_state::AppState>& appState) {
  setWindowTitle("Preview");

  auto* imagePreview = new ImagePreviewWidget();
  imagePreview->init(appState);
  setWidget(imagePreview);
}

} // namespace qt_file_explorer::widgets
