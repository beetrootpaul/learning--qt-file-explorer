#ifndef QT_FILE_EXPLORER_SRC_MAIN_WINDOW_H
#define QT_FILE_EXPLORER_SRC_MAIN_WINDOW_H

#include <QMainWindow>

namespace qt_file_explorer {

class MainWindow : public QMainWindow {

public:
  MainWindow();
  void closeEvent(QCloseEvent* event) override;

private:
  void writeSettings();
  void readSettings();

};

} // namespace qt_file_explorer

#endif //QT_FILE_EXPLORER_SRC_MAIN_WINDOW_H
