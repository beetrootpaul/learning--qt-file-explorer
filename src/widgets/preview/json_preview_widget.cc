#include "json_preview_widget.h"

#include <QFile>
#include <QFileInfo>
#include <QSizePolicy>

namespace qt_file_explorer::widgets {

JsonPreviewWidget::JsonPreviewWidget() {
  qDebug() << "+" << this;
}

JsonPreviewWidget::~JsonPreviewWidget() {
  qDebug() << "~" << this;
}

void JsonPreviewWidget::init() {
  // Prevent this QLabel from expanding to match longer text lines.
  setSizePolicy(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored);

  QFont font;
  font.setStyleHint(QFont::Monospace);
  font = QFont(font.defaultFamily());
  setFont(font);

  setMargin(8);
  setAlignment(Qt::AlignTop | Qt::AlignLeft);
  setWordWrap(true);
}

bool JsonPreviewWidget::canPreview(const QString& path) {
  QFileInfo fileInfo(path);
  if (!fileInfo.isReadable()) return false;

  const auto& extension = fileInfo.suffix().toLower();
  return extension == "json";
}

void JsonPreviewWidget::preview(QString path) {
  QFile file(path);
  file.open(QIODeviceBase::OpenModeFlag::ReadOnly);
  // TODO: thread?
  // TODO: caching?
  const QByteArray& array = file.readAll();
  file.close();
  
  setText(array);
}

void JsonPreviewWidget::clear() {
  setText("");
}

QWidget* JsonPreviewWidget::asQWidget() {
  return this;
}

} // namespace qt_file_explorer::widgets
