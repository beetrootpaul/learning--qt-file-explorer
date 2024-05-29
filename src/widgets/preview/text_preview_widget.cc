#include "text_preview_widget.h"

#include <QFile>
#include <QFileInfo>
#include <QSizePolicy>

namespace qt_file_explorer::widgets {

TextPreviewWidget::TextPreviewWidget() {
  qDebug() << "+" << this;
}

TextPreviewWidget::~TextPreviewWidget() {
  qDebug() << "~" << this;
}

// TODO: enforce it through interface
void TextPreviewWidget::init() {
  // Prevent this QLabel from expanding to match longer text lines.
  setSizePolicy(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored);

  // TODO: implement MD rendered and use this:
//  setTextFormat(Qt::TextFormat::MarkdownText);

  setMargin(8);
  setAlignment(Qt::AlignTop | Qt::AlignLeft);
  setWordWrap(true);
}

bool TextPreviewWidget::canPreview(const QString& path) {
  QFileInfo fileInfo(path);
  if (!fileInfo.isReadable()) return false;

  const auto& extension = fileInfo.suffix().toLower();
  return extension == "txt";
}

void TextPreviewWidget::preview(QString path) {
  QFile file(path);
  file.open(QIODeviceBase::OpenModeFlag::ReadOnly);
  // TODO: thread?
  // TODO: caching?
  const QByteArray& array = file.readAll();

  setText(array);
}

void TextPreviewWidget::clear() {
  setText("");
}

QWidget* TextPreviewWidget::asQWidget() {
  return this;
}

} // namespace qt_file_explorer
