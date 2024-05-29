#ifndef QT_FILE_EXPLORER_WIDGETS_PREVIEW_MARKDOWN_PREVIEW_WIDGET_H
#define QT_FILE_EXPLORER_WIDGETS_PREVIEW_MARKDOWN_PREVIEW_WIDGET_H

#include <QLabel>
#include <QObject>

#include "with_preview_capability.h"

namespace qt_file_explorer::widgets {

class MarkdownPreviewWidget : public QLabel, public WithPreviewCapability {

Q_OBJECT

public:
  MarkdownPreviewWidget();
  ~MarkdownPreviewWidget();

  void init();

  bool canPreview(const QString& path) override;
  void preview(QString path) override;
  void clear() override;

  QWidget* asQWidget() override;
};

} // namespace qt_file_explorer::widgets

#endif //QT_FILE_EXPLORER_WIDGETS_PREVIEW_MARKDOWN_PREVIEW_WIDGET_H
