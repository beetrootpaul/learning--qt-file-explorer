#ifndef QT_FILE_EXPLORER_WIDGETS_PREVIEW_TEXT_PREVIEW_WIDGET_H
#define QT_FILE_EXPLORER_WIDGETS_PREVIEW_TEXT_PREVIEW_WIDGET_H

#include <QObject>
#include <QPlainTextEdit>

#include "with_preview_capability.h"

namespace qt_file_explorer::widgets {

class TextPreviewWidget : public QPlainTextEdit, public WithPreviewCapability {

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

} // namespace qt_file_explorer::widgets

#endif //QT_FILE_EXPLORER_WIDGETS_PREVIEW_TEXT_PREVIEW_WIDGET_H
