#include "file_name_preview_widget.h"

#include <QFileInfo>
#include <QSizePolicy>

namespace qt_file_explorer::widgets {

FileNamePreviewWidget::FileNamePreviewWidget() {
  qDebug() << "+" << this;
}

FileNamePreviewWidget::~FileNamePreviewWidget() {
  qDebug() << "~" << this;
}

// TODO: enforce init definition through interface
void FileNamePreviewWidget::init() {
  // Prevent this QLabel from expanding to match longer file names.
  setSizePolicy(
      QSizePolicy(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored));

  setMargin(8);
  setAlignment(Qt::AlignTop | Qt::AlignLeft);
  setWordWrap(true);
}

bool FileNamePreviewWidget::canPreview(const QString& path) {
  return true;
}

void FileNamePreviewWidget::preview(QString path) {
  QFileInfo fileInfo(path);
  setText(fileInfo.fileName());
  // TODO: make it e.g. centered
}

void FileNamePreviewWidget::clear() {
  setText("");
}

QWidget* FileNamePreviewWidget::asQWidget() {
  return this;
}

} // namespace qt_file_explorer::widgets
