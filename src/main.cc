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

  auto* model = new qt_file_explorer::model::Model();
  main_window.setModel(model);

  // Trigger slots listening to this signal. Thanks to that we do
  // not have to add initialization code and can rely on slots only.
  model->changed();

  main_window.show();

  return QApplication::exec();
}
