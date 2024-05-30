#ifndef QT_FILE_EXPLORER_WIDGETS_PREVIEW_FILE_NAME_PREVIEW_WIDGET_H
#define QT_FILE_EXPLORER_WIDGETS_PREVIEW_FILE_NAME_PREVIEW_WIDGET_H

#include <QLabel>
#include <QObject>

#include "with_preview_capability.h"

namespace qt_file_explorer::gui {

class FileNamePreviewWidget : public QLabel, public WithPreviewCapability {

Q_OBJECT

public:
  FileNamePreviewWidget();
  ~FileNamePreviewWidget();

  void init();

  bool canPreview(const QString& path) override;
  void preview(QString path) override;
  void clear() override;

  QWidget* asQWidget() override;

};

} // namespace qt_file_explorer::gui

#endif //QT_FILE_EXPLORER_WIDGETS_PREVIEW_FILE_NAME_PREVIEW_WIDGET_H
