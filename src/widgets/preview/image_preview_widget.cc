#include "image_preview_widget.h"

#include <QGuiApplication>
#include <QImageReader>
#include <QMessageBox>
#include <QPainter>

namespace qt_file_explorer {

// TODO: threading for bigger images? Can be checked by experiencing a bit of a freeze when quickly changing selection over a huge file, with arrow keys

// TODO: implement text rendering for txt and md files. For all other do a "null" renderer which just shows the filename

ImagePreviewWidget::ImagePreviewWidget() {
  qDebug() << "+" << this;
}

ImagePreviewWidget::~ImagePreviewWidget() {
  qDebug() << "~" << this;
}

void
ImagePreviewWidget::init(const QSharedPointer<app_state::AppState>& appState) {
  appState_ = appState;

  connect(appState_.data(), &app_state::AppState::signalSelectedPathChanged,
          this, &ImagePreviewWidget::slotUpdateImage);
}

void ImagePreviewWidget::slotUpdateImage() {
  pixmap_ = QPixmap(appState_->selectedPath());
  repaint();
}

void ImagePreviewWidget::paintEvent(QPaintEvent* event) {
  QLabel::paintEvent(event);

  if (pixmap_.isNull()) return;

  auto imageSize = pixmap_.size();
  auto previewSize = size();

  // Detect how much to resize the image to fit within the preview area.
  float ratio = std::min(static_cast<float>(previewSize.width()) /
                         static_cast<float>(imageSize.width()),
                         static_cast<float>(previewSize.height()) /
                         static_cast<float>(imageSize.height()));

  // Prevent image upscaling.
  ratio = std::min(ratio, 1.0f);

  auto adjustedImageSize = imageSize * ratio;

  QPixmap adjustedPixmap = pixmap_.scaledToWidth(adjustedImageSize.width(),
                                                 Qt::TransformationMode::SmoothTransformation);

  // Find a drawing positing that would make the image centered within the preview area.
  auto offset = QPoint((previewSize.width() - adjustedImageSize.width()) / 2,
                       (previewSize.height() - adjustedImageSize.height()) / 2);

  QPainter painter(this);
  painter.drawPixmap(offset, adjustedPixmap);
}

} // namespace qt_file_explorer
