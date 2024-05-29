#ifndef QT_FILE_EXPLORER_WIDGETS_PREVIEW_IMAGE_PREVIEW_WIDGET_H
#define QT_FILE_EXPLORER_WIDGETS_PREVIEW_IMAGE_PREVIEW_WIDGET_H

#include <QLabel>
#include <QObject>

#include "with_preview_capability.h"

namespace qt_file_explorer::widgets {

class ImagePreviewWidget : public QLabel, public WithPreviewCapability {

Q_OBJECT

public:
  ImagePreviewWidget();
  ~ImagePreviewWidget();

  void init();

  bool canPreview(const QString& path) override;
  void preview(QString path) override;
  void clear() override;

  QWidget* asQWidget() override;

private:
  const QList<QString> acceptedImageExtensions_ = QList<QString>{"gif", "jpg",
                                                                 "png"};
  QPixmap pixmap_;

  void paintEvent(QPaintEvent* event) override;

};

} // namespace qt_file_explorer::widgets

#endif //QT_FILE_EXPLORER_WIDGETS_PREVIEW_IMAGE_PREVIEW_WIDGET_H
