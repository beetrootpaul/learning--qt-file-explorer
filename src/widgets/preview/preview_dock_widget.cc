#include "preview_dock_widget.h"

#include <QSharedPointer>

#include "image_preview_widget.h"
#include "file_name_preview_widget.h"

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
  appState_ = appState;

  setWindowTitle("Preview");

  auto* imagePreview = new ImagePreviewWidget();
  imagePreview->init();
  orderedPreviewWidgets_.push_back(
      QSharedPointer<WithPreviewCapability>(imagePreview));
  auto* fileNamePreview = new FileNamePreviewWidget();
  fileNamePreview->init();
  orderedPreviewWidgets_.push_back(
      QSharedPointer<WithPreviewCapability>(fileNamePreview));

  setWidget(imagePreview);

  connect(appState_.data(), &app_state::AppState::signalSelectedPathChanged,
          this, &PreviewDockWidget::slotUpdatePreview);
}

void PreviewDockWidget::slotUpdatePreview() {
  auto path = appState_->selectedPath();

  bool handled = false;
  for (auto pw: orderedPreviewWidgets_) {
    if (!handled && pw->canPreview(path)) {
      handled = true;
      setWidget(pw->asQWidget());
      pw->preview(path);
    } else {
      pw->clear();
    }
  }
}

} // namespace qt_file_explorer::widgets
