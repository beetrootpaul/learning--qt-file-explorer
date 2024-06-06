#ifndef QT_FILE_EXPLORER_WIDGETS_PREVIEW_MARKDOWN_PREVIEW_WIDGET_H
#define QT_FILE_EXPLORER_WIDGETS_PREVIEW_MARKDOWN_PREVIEW_WIDGET_H

#include <QObject>
#include <QTextEdit>

#include "preview_widget.h"

namespace qt_file_explorer::gui {

class MarkdownPreviewWidget
    : public QTextEdit, public PreviewWidget {

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

} // namespace qt_file_explorer::gui

#endif //QT_FILE_EXPLORER_WIDGETS_PREVIEW_MARKDOWN_PREVIEW_WIDGET_H
