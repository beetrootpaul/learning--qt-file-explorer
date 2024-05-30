#ifndef QT_FILE_EXPLORER_WIDGETS_PREVIEW_WITH_PREVIEW_CAPABILITY_H
#define QT_FILE_EXPLORER_WIDGETS_PREVIEW_WITH_PREVIEW_CAPABILITY_H

#include <QString>

namespace qt_file_explorer::gui {

class WithPreviewCapability {

public:
  virtual bool canPreview(const QString& path) = 0;
  virtual void preview(QString path) = 0;
  virtual void clear() = 0;

  // This method serves as a way to avoid unnecessary complex types
  // based on templates for any class that implements `WithPreviewCapability`.
  // Specifically, `QDockWidget::setWidget` requires `QWidget` as its param.
  virtual QWidget* asQWidget() = 0;

};

} // namespace qt_file_explorer::gui

#endif //QT_FILE_EXPLORER_WIDGETS_PREVIEW_WITH_PREVIEW_CAPABILITY_H
