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

//  int imageWidth = srcPixmap_.width();
//  int imageHeight = srcPixmap_.height();
//  float labelWidth = this->width();
//  float labelHeight = this->height();
//  qDebug() << labelWidth << labelHeight;
//  float ratio = std::min(labelWidth / imageWidth, labelHeight / imageHeight);
//  bool shouldScale = (imageWidth > labelWidth) || (imageHeight > labelHeight);
//  float newWidth = shouldScale ? imageWidth * ratio : imageWidth;
//  float newHeight = shouldScale ? imageHeight * ratio : imageHeight;
//  // TODO: "QPixmap::operator=: Cannot assign to pixmap during painting"
//  QPixmap newPixmap = srcPixmap_.scaledToWidth(newWidth,
//                                               Qt::TransformationMode::SmoothTransformation);
//  qDebug() << newPixmap.width() << newPixmap.height();
//  int x = std::abs(newWidth - labelWidth) / 2;
//  int y = std::abs(newHeight - labelHeight) / 2;
//  qDebug() << x << y;
//  QPainter painter(this);
//  painter.drawPixmap(x, y, newPixmap);
}

} // namespace qt_file_explorer
