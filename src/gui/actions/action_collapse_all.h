#ifndef QT_FILE_EXPLORER_GUI_ACTIONS_ACTION_COLLAPSE_ALL_H
#define QT_FILE_EXPLORER_GUI_ACTIONS_ACTION_COLLAPSE_ALL_H

#include <QAction>
#include <QObject>

#include "../dir_picker/dir_picker_widget.h"

namespace qt_file_explorer::gui {

class ActionCollapseAll : public QAction {

Q_OBJECT

public:
  ActionCollapseAll(QObject* parent, DirPickerWidget* dirPicker);
  ~ActionCollapseAll();

private:
  DirPickerWidget* dirPicker_ = nullptr;

private slots:
  void perform();

};

} // namespace qt_file_explorer::gui

#endif //QT_FILE_EXPLORER_GUI_ACTIONS_ACTION_COLLAPSE_ALL_H
