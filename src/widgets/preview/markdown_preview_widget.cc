#include "markdown_preview_widget.h"

#include <QFile>
#include <QFileInfo>
#include <QSizePolicy>

#include "../monospace_font.h"

namespace qt_file_explorer::widgets {

MarkdownPreviewWidget::MarkdownPreviewWidget() {
  qDebug() << "+" << this;
}

MarkdownPreviewWidget::~MarkdownPreviewWidget() {
  qDebug() << "~" << this;
}

void MarkdownPreviewWidget::init() {
  setReadOnly(true);
  setLineWrapMode(QTextEdit::LineWrapMode::WidgetWidth);
  applyMonospaceFontOn(this);
}

bool MarkdownPreviewWidget::canPreview(const QString& path) {
  QFileInfo fileInfo(path);
  if (!fileInfo.isReadable()) return false;

  const auto& extension = fileInfo.suffix().toLower();
  return extension == "md";
}

void MarkdownPreviewWidget::preview(QString path) {
  qDebug() << "MD preview:" << path;

  clear();

  QFile file(path);
  if (file.open(QIODeviceBase::OpenModeFlag::ReadOnly)) {
    setMarkdown(file.readAll());
    file.close();
  }
}

void MarkdownPreviewWidget::clear() {
  setMarkdown("");
}

QWidget* MarkdownPreviewWidget::asQWidget() {
  return this;
}

} // namespace qt_file_explorer::widgets
