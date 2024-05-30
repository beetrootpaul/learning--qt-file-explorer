#include "image_preview_widget.h"

#include <QFileInfo>
#include <QGuiApplication>
#include <QImageReader>
#include <QMessageBox>
#include <QPainter>
#include <QtConcurrent>

namespace qt_file_explorer::widgets {

ImagePreviewWidget::ImagePreviewWidget() {
  qDebug() << "+" << this;
}

ImagePreviewWidget::~ImagePreviewWidget() {
  qDebug() << "~" << this;
}

void ImagePreviewWidget::init() {
  // These adjustments will be used by "loading…" text, which is visible
  // for a moment when a bigger image is being loaded.
  setMargin(8);
  setAlignment(Qt::AlignTop | Qt::AlignLeft);

  connect(&imageLoadingWatcher_, &QFutureWatcher<QPixmap>::finished, this,
          &ImagePreviewWidget::slotImageLoaded);
}

bool ImagePreviewWidget::canPreview(const QString& path) {
  QFileInfo fileInfo(path);
  if (!fileInfo.isReadable()) return false;

  const auto& extension = fileInfo.suffix().toLower();

  // We are checking against `supportedImageFormats()`, because according
  // to docs this corresponds to what `QPixmap` can render later on.
  return QImageReader::supportedImageFormats().contains(extension);
}

void ImagePreviewWidget::preview(QString path) {
  qDebug() << "IMG preview:" << path;

  clear();

  setText("loading…");
  imageLoadingWatcher_.cancel();
  imageLoadingWatcher_.setFuture(QtConcurrent::run([=] {
    return QPixmap(path);
  }));
}

void ImagePreviewWidget::slotImageLoaded() {
  if (imageLoadingWatcher_.isCanceled()) return;

  pixmap_ = imageLoadingWatcher_.result();

  setText("");
  repaint();
}

void ImagePreviewWidget::clear() {
  pixmap_ = QPixmap();
  setText("");
  repaint();
  imageLoadingWatcher_.cancel();
}

QWidget* ImagePreviewWidget::asQWidget() {
  return this;
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

} // namespace qt_file_explorer::widgets
