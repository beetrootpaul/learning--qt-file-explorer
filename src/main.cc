#include <iostream>

#include <QApplication>
#include <QHBoxLayout>

#include "widgets/main_window.h"
#include "model/model.h"

// TODO: group some files into dirs

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  QCoreApplication::setOrganizationName("Beetroot Paul");
  QCoreApplication::setOrganizationDomain("beetrootpaul.com");
  QCoreApplication::setApplicationName("QtFileExplorer");

  auto main_window = qt_file_explorer::widgets::MainWindow();
  main_window.setModel(new qt_file_explorer::model::Model());
  main_window.show();

  return QApplication::exec();
}
