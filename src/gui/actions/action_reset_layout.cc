#include "action_reset_layout.h"

namespace qt_file_explorer::gui {

ActionResetLayout::ActionResetLayout(QObject* parent, MainWindow* mainWindow)
    : QAction(parent), mainWindow_(mainWindow) {
  setObjectName("ActionResetLayout");

  qDebug() << "+" << this;

  setText(tr("Reset layout"));
  setShortcut(Qt::META | Qt::Key_R);

  connect(this, &QAction::triggered, this, &ActionResetLayout::perform);
}

ActionResetLayout::~ActionResetLayout() {
  qDebug() << "~" << this;
}

void ActionResetLayout::perform() {
  qDebug() << "! ActionResetLayout";
  if (mainWindow_) {
    mainWindow_->resetLayout();
  }
}

} // namespace qt_file_explorer::gui
