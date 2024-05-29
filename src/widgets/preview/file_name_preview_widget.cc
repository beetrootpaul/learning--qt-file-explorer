#include "file_name_preview_widget.h"

#include <QFileInfo>

namespace qt_file_explorer::widgets {

FileNamePreviewWidget::FileNamePreviewWidget() {
  qDebug() << "+" << this;
}

FileNamePreviewWidget::~FileNamePreviewWidget() {
  qDebug() << "~" << this;
}

// TODO: enforce it through interface
void FileNamePreviewWidget::init() {}

bool FileNamePreviewWidget::canPreview(const QString& path) {
  return true;
}

void FileNamePreviewWidget::preview(QString path) {
  QFileInfo fileInfo(path);
  setText(fileInfo.fileName());
}

void FileNamePreviewWidget::clear() {
  setText("");
}

QWidget* FileNamePreviewWidget::asQWidget() {
  return this;
}

} // namespace qt_file_explorer::widgets
