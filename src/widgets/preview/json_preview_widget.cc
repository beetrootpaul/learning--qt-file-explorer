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

  // NOTE: Even if surprising, I managed to get the most consistent nicely looking
  // results when doing as below: creating first font, setting its hint, then
  // creating a second one based on `defaultFamily()` from that first one.
  // Using just one font instance seemed to not work as expected, even with
  // a `QFont("")` constructor. On the other hand: using `QFont("Monospace")` was
  // seemingly OK, but with a risk that it worked only due to a given machine
  // having "Monospace" font family available.
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
  qDebug() << "JSON preview:" << path;

  clear();

  QFile file(path);
  if (file.open(QIODeviceBase::OpenModeFlag::ReadOnly)) {
    setText(file.readAll());
    file.close();
  }
}

void JsonPreviewWidget::clear() {
  setText("");
}

QWidget* JsonPreviewWidget::asQWidget() {
  return this;
}

} // namespace qt_file_explorer::widgets
