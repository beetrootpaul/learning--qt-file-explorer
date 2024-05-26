#ifndef QT_FILE_EXPLORER_SRC_MAIN_WINDOW_H
#define QT_FILE_EXPLORER_SRC_MAIN_WINDOW_H

#include <QMainWindow>

#include "file_explorer.h"
#include "model.h"

namespace qt_file_explorer::widgets {

class MainWindow : public QMainWindow {

public:
  MainWindow();

  void closeEvent(QCloseEvent* event) override;

  void setModel(model::Model* model);

private:
  FileExplorer* file_explorer_;

  void savePersistedState();
  void restorePersistedState();

};

} // namespace qt_file_explorer::widgets

#endif //QT_FILE_EXPLORER_SRC_MAIN_WINDOW_H
