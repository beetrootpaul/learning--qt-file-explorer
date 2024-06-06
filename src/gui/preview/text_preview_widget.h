#ifndef QT_FILE_EXPLORER_WIDGETS_PREVIEW_TEXT_PREVIEW_WIDGET_H
#define QT_FILE_EXPLORER_WIDGETS_PREVIEW_TEXT_PREVIEW_WIDGET_H

#include <QObject>
#include <QPlainTextEdit>

#include "preview_widget.h"

namespace qt_file_explorer::gui {

class TextPreviewWidget : public QPlainTextEdit, public PreviewWidget {

Q_OBJECT

public:
  TextPreviewWidget();
  ~TextPreviewWidget();

  void init();

  bool canPreview(const QString& path) override;
  void preview(QString path) override;
  void clear() override;

  QWidget* asQWidget() override;
};

} // namespace qt_file_explorer::gui

#endif //QT_FILE_EXPLORER_WIDGETS_PREVIEW_TEXT_PREVIEW_WIDGET_H
