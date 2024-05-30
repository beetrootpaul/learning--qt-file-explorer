#include "file_name_preview_widget.h"

#include <QFileInfo>
#include <QSizePolicy>

namespace qt_file_explorer::gui {

FileNamePreviewWidget::FileNamePreviewWidget() {
  qDebug() << "+" << this;
}

FileNamePreviewWidget::~FileNamePreviewWidget() {
  qDebug() << "~" << this;
}

void FileNamePreviewWidget::init() {
  // Prevent this QLabel from expanding to match longer file names.
  setSizePolicy(QSizePolicy::Policy::Ignored, QSizePolicy::Policy::Ignored);

  setMargin(8);
  setAlignment(Qt::AlignTop | Qt::AlignLeft);
  setWordWrap(true);
}

bool FileNamePreviewWidget::canPreview(const QString& path) {
  return true;
}

void FileNamePreviewWidget::preview(QString path) {
  qDebug() << "FILENAME preview:" << path;

  clear();

  QFileInfo fileInfo(path);
  setText(fileInfo.fileName());
}

void FileNamePreviewWidget::clear() {
  setText("");
}

QWidget* FileNamePreviewWidget::asQWidget() {
  return this;
}

} // namespace qt_file_explorer::gui
