#ifndef QT_FILE_EXPLORER_GUI_ACTIONS_ACTION_RESET_LAYOUT_H
#define QT_FILE_EXPLORER_GUI_ACTIONS_ACTION_RESET_LAYOUT_H

#include <QAction>
#include <QObject>

#include "../main_window.h"

namespace qt_file_explorer::gui {

class ActionResetLayout : public QAction {

Q_OBJECT

public:
  ActionResetLayout(QObject* parent, MainWindow* mainWindow);
  ~ActionResetLayout();

private:
  MainWindow* mainWindow_ = nullptr;

private slots:
  void perform();

};

} // namespace qt_file_explorer::gui

#endif //QT_FILE_EXPLORER_GUI_ACTIONS_ACTION_RESET_LAYOUT_H
