#include "markdown_preview_widget.h"

#include <QFile>
#include <QFileInfo>
#include <QSizePolicy>

namespace qt_file_explorer::widgets {

MarkdownPreviewWidget::MarkdownPreviewWidget() {
  qDebug() << "+" << this;
}

MarkdownPreviewWidget::~MarkdownPreviewWidget() {
  qDebug() << "~" << this;
}

void MarkdownPreviewWidget::init() {
  // Prevent this QLabel from expanding to match longer text lines.
  setSizePolicy(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored);

  setTextFormat(Qt::TextFormat::MarkdownText);

  setMargin(8);
  setAlignment(Qt::AlignTop | Qt::AlignLeft);
  setWordWrap(true);
}

bool MarkdownPreviewWidget::canPreview(const QString& path) {
  QFileInfo fileInfo(path);
  if (!fileInfo.isReadable()) return false;

  const auto& extension = fileInfo.suffix().toLower();
  return extension == "md";
}

void MarkdownPreviewWidget::preview(QString path) {
  QFile file(path);
  file.open(QIODeviceBase::OpenModeFlag::ReadOnly);
  // TODO: thread?
  // TODO: caching?
  const QByteArray& array = file.readAll();
  file.close();

  // TODO: ? HERE ?
//  setText(array);
}

void MarkdownPreviewWidget::clear() {
  setText("");
}

QWidget* MarkdownPreviewWidget::asQWidget() {
  return this;
}

} // namespace qt_file_explorer::widgets
