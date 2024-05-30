#include "text_preview_widget.h"

#include <QFile>
#include <QFileInfo>
#include <QSizePolicy>

#include "../monospace_font.h"

namespace qt_file_explorer::widgets {

TextPreviewWidget::TextPreviewWidget() {
  qDebug() << "+" << this;
}

TextPreviewWidget::~TextPreviewWidget() {
  qDebug() << "~" << this;
}

// TODO: enforce it through interface
void TextPreviewWidget::init() {
  setReadOnly(true);

  setLineWrapMode(QPlainTextEdit::LineWrapMode::WidgetWidth);

  applyMonospaceFontOn(this);
}

bool TextPreviewWidget::canPreview(const QString& path) {
  QFileInfo fileInfo(path);
  if (!fileInfo.isReadable()) return false;

  const auto& extension = fileInfo.suffix().toLower();
  return extension == "txt";
}

void TextPreviewWidget::preview(QString path) {
  qDebug() << "TEXT preview:" << path;

  clear();

  QFile file(path);
  if (file.open(QIODeviceBase::OpenModeFlag::ReadOnly)) {
    setPlainText(file.readAll());
    file.close();
  }
}

void TextPreviewWidget::clear() {
  setPlainText("");
}

QWidget* TextPreviewWidget::asQWidget() {
  return this;
}

} // namespace qt_file_explorer
