#include "json_preview_widget.h"

#include <QFile>
#include <QFileInfo>
#include <QSizePolicy>

#include "../monospace_font.h"

namespace qt_file_explorer::gui {

JsonPreviewWidget::JsonPreviewWidget() {
  qDebug() << "+" << this;
}

JsonPreviewWidget::~JsonPreviewWidget() {
  qDebug() << "~" << this;
}

void JsonPreviewWidget::init() {
  setReadOnly(true);
  setLineWrapMode(QPlainTextEdit::LineWrapMode::WidgetWidth);
  applyMonospaceFontOn(this);
}

bool JsonPreviewWidget::canPreview(const QString& path) {
  QFileInfo fileInfo(path);
  if (!fileInfo.isReadable()) return false;

  const auto& extension = fileInfo.suffix().toLower();
  return extension == "json";
}

void JsonPreviewWidget::preview(QString path) {
  qDebug() << "JSON preview:" << path;

  clear();

  QFile file(path);
  if (file.open(QIODeviceBase::OpenModeFlag::ReadOnly)) {
    setPlainText(file.readAll());
    file.close();
  }
}

void JsonPreviewWidget::clear() {
  setPlainText("");
}

QWidget* JsonPreviewWidget::asQWidget() {
  return this;
}

} // namespace qt_file_explorer::gui
