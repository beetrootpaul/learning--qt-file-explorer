#ifndef QT_FILE_EXPLORER_WIDGETS_PREVIEW_IMAGE_PREVIEW_WIDGET_H
#define QT_FILE_EXPLORER_WIDGETS_PREVIEW_IMAGE_PREVIEW_WIDGET_H

#include <QFutureWatcher>
#include <QLabel>
#include <QObject>

#include "preview_widget.h"

namespace qt_file_explorer::gui {

class ImagePreviewWidget : public QLabel, public PreviewWidget {

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
  QFutureWatcher<QPixmap> imageLoadingWatcher_ = QFutureWatcher<QPixmap>();
  QPixmap pixmap_;

  void paintEvent(QPaintEvent* event) override;

private slots:
  void slotImageLoaded();

};

} // namespace qt_file_explorer::gui

#endif //QT_FILE_EXPLORER_WIDGETS_PREVIEW_IMAGE_PREVIEW_WIDGET_H
