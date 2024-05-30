#include "action_collapse_all.h"

namespace qt_file_explorer::gui {

ActionCollapseAll::ActionCollapseAll(QObject* parent,
                                     DirPickerWidget* dirPicker) : QAction(
    parent), dirPicker_(dirPicker) {
  setObjectName("ActionCollapseAll");

  qDebug() << "+" << this;

  setText(tr("Collapse all"));

  connect(this, &QAction::triggered, this, &ActionCollapseAll::perform);
}

ActionCollapseAll::~ActionCollapseAll() {
  qDebug() << "~" << this;
}

void ActionCollapseAll::perform() {
  qDebug() << "! ActionCollapseAll";
  if (dirPicker_) {
    dirPicker_->collapseAll();
  }
}

} // namespace qt_file_explorer::gui
