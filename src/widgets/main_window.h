#ifndef QT_FILE_EXPLORER_SRC_MAIN_WINDOW_H
#define QT_FILE_EXPLORER_SRC_MAIN_WINDOW_H

#include <QMainWindow>
#include <QPushButton>

#include "file_explorer.h"
#include "../model/model.h"

namespace qt_file_explorer::widgets {

class MainWindow : public QMainWindow {

public:
  MainWindow();

  void closeEvent(QCloseEvent* event) override;

  void setModel(model::Model* model);

private:
  model::Model* model_;
  FileExplorer* file_explorer_;
  QPushButton* toggle_dir_listing_view_type_;

  void savePersistedState();
  void restorePersistedState(bool layoutOnly = false);

};

} // namespace qt_file_explorer::widgets

#endif //QT_FILE_EXPLORER_SRC_MAIN_WINDOW_H
