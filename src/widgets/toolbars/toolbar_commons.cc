#include "toolbar_commons.h"

namespace qt_file_explorer::widgets {

void applyCommonToolbarConfiguration(QToolBar* toolbar, QString name) {
  // Object name is required for state serialization
  toolbar->setObjectName(name);

  toolbar->setMovable(true);
  toolbar->setFloatable(false);

// Remove context menu in order to remove the ability to close this mainToolbar_
  toolbar->setContextMenuPolicy(Qt::ContextMenuPolicy::PreventContextMenu);
}

} // namespace qt_file_explorer::widgets
