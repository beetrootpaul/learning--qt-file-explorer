#ifndef QT_FILE_EXPLORER_SRC_MAIN_WINDOW_H
#define QT_FILE_EXPLORER_SRC_MAIN_WINDOW_H

#include <QMainWindow>

#include "directory_picker_widget.h"
#include "directory_listing_widget.h"
#include "model.h"

namespace qt_file_explorer::widgets {

class MainWindow : public QMainWindow {

public:
  MainWindow();

  void closeEvent(QCloseEvent* event) override;

  void setModel(qt_file_explorer::model::Model* model);

private:
  // TODO: Do I need to delete them in the window's destructor?
  DirectoryPickerWidget* directory_picker_;
  DirectoryListingWidget* directory_listing_;

  void writeSettings();
  void readSettings();

};

} // namespace qt_file_explorer::widgets

#endif //QT_FILE_EXPLORER_SRC_MAIN_WINDOW_H
