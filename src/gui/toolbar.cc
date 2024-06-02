#include "toolbar.h"

namespace qt_file_explorer::gui {

Toolbar::Toolbar(const QString& objectName) {
  // Object name is required for state serialization.
  setObjectName(objectName);

  qDebug() << "+" << this;

  setMovable(true);
  setFloatable(false);

  // Remove context menu in order to remove the ability to close this toolbar or other app toolbars or the preview dock.
  setContextMenuPolicy(Qt::ContextMenuPolicy::PreventContextMenu);
}

Toolbar::~Toolbar() {
  qDebug() << "-" << this;
}

} // namespace qt_file_explorer::gui
