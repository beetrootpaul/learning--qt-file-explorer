#ifndef QT_FILE_EXPLORER_GUI_TOOLBAR_H
#define QT_FILE_EXPLORER_GUI_TOOLBAR_H

#include <QObject>
#include <QToolBar>

namespace qt_file_explorer::gui {

class Toolbar : public QToolBar {

Q_OBJECT

public:
  Toolbar(const QString& objectName);
  ~Toolbar();
};

} // namespace qt_file_explorer::gui

#endif //QT_FILE_EXPLORER_GUI_TOOLBAR_H
