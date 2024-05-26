#include "main_window.h"

#include <iostream>

#include <QPushButton>
#include <QSettings>
#include <QSplitter>
#include <QToolBar>

#include "directory_listing_widget.h"
#include "directory_picker_widget.h"

namespace qt_file_explorer::widgets {

MainWindow::MainWindow() {
  setWindowTitle("Qt File Explorer");

  directory_picker_ = new DirectoryPickerWidget();
  directory_listing_ = new DirectoryListingWidget();

  auto* splitter = new QSplitter();
  splitter->setOrientation(Qt::Orientation::Horizontal);
  splitter->addWidget(directory_picker_);
  splitter->addWidget(directory_listing_);

  setCentralWidget(splitter);

  auto* toolbar = new QToolBar("t 1111");
  toolbar->setObjectName("t1");
  toolbar->addWidget(new QPushButton("asdadsad"));
  addToolBar(toolbar);
  auto* toolbar2 = new QToolBar("tttt 2");
  toolbar2->setObjectName("t2");
  toolbar2->addWidget(new QPushButton("222222"));
  addToolBar(toolbar2);

  readSettings();
}

void MainWindow::closeEvent(QCloseEvent* event) {
  writeSettings();
  QMainWindow::closeEvent(event);
}

void MainWindow::setModel(qt_file_explorer::model::Model* model) {
  directory_picker_->setCurrentPath(model->currentPath());
  directory_listing_->setCurrentPath(model->currentPath());
}

void MainWindow::readSettings() {
  std::cout << "READ SETTINGS" << std::endl;

  QSettings settings;

  const auto size = settings.value("layout/main_window/size").toSize();
  if (size.isEmpty()) {
    std::cout << "! empty size !" << std::endl;
    resize(800, 600);
  } else {
    std::cout << "~ restore size ~" << std::endl;
    resize(size);
  }

  const auto pos = settings.value("layout/main_window/pos").toPoint();
  if (pos.isNull()) {
    std::cout << "! empty pos !" << std::endl;
    // TODO: make it centered
    move(10, 10);
  } else {
    std::cout << "~ restore pos ~" << std::endl;
    // TODO: make it always visible even if screen size decreases
    move(pos);
  }

  const auto state = settings.value("layout/main_window/state",
                                    QByteArray()).toByteArray();
  if (state.isEmpty()) {
    std::cout << "! empty state !" << std::endl;
  } else {
    std::cout << "~ restore state ~" << std::endl;
    restoreState(state);
  }
}

void MainWindow::writeSettings() {
  std::cout << "WRITE SETTINGS" << std::endl;

  QSettings settings;
  // TODO: extract key constants
  settings.setValue("layout/main_window/size", size());
  settings.setValue("layout/main_window/pos", pos());
  settings.setValue("layout/main_window/state", saveState());
}

} // namespace qt_file_explorer::widgets
