#include "view_toolbar_widget.h"

#include <QPushButton>
#include <QSettings>

#include "toolbar_commons.h"

namespace qt_file_explorer::widgets {

ViewToolbarWidget::ViewToolbarWidget() {
  qDebug() << "+" << this;
}

ViewToolbarWidget::~ViewToolbarWidget() {
  qDebug() << "~" << this;
}

void ViewToolbarWidget::init() {
  applyCommonToolbarConfiguration(this, "view_toolbar");

  // TODO: shortcut. The `&R` does not work, apparently
  auto* resetLayoutButton = new QPushButton("&Reset layout");
  connect(resetLayoutButton, &QPushButton::clicked, [=]() {
    emit signalResetLayoutClicked();
  });
  addWidget(resetLayoutButton);
}

} // namespace qt_file_explorer::widgets
