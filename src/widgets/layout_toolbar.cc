#include "layout_toolbar.h"

#include <QPushButton>
#include <QSettings>

#include "toolbar_commons.h"

namespace qt_file_explorer::widgets {

LayoutToolbar::LayoutToolbar() {
  qDebug() << "+" << this;
}

LayoutToolbar::~LayoutToolbar() {
  qDebug() << "~" << this;
}

void LayoutToolbar::init() {
  applyCommonToolbarConfiguration(this, "layout_toolbar");

  // TODO: shortcut. The `&R` does not work, apparently
  auto* resetLayoutButton = new QPushButton("&Reset layout");
  connect(resetLayoutButton, &QPushButton::clicked, [=]() {
    emit signalResetLayoutClicked();
  });
  addWidget(resetLayoutButton);
}

} // namespace qt_file_explorer::widgets
