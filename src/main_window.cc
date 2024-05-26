#include "main_window.h"

#include <iostream>

#include <QPushButton>
#include <QSettings>
#include <QToolBar>

#include "file_explorer.h"

namespace qt_file_explorer::widgets {

MainWindow::MainWindow() {
  setWindowTitle("Qt File Explorer");

  file_explorer_ = new FileExplorer();
  setCentralWidget(file_explorer_);

  auto* toolbar = new QToolBar("t 1111");
  toolbar->setObjectName("t1");
  toolbar->addWidget(new QPushButton("asdadsad"));
  addToolBar(toolbar);
  auto* toolbar2 = new QToolBar("tttt 2");
  toolbar2->setObjectName("t2");
  toolbar2->addWidget(new QPushButton("222222"));
  addToolBar(toolbar2);

  restorePersistedState();
}

void MainWindow::closeEvent(QCloseEvent* event) {
  savePersistedState();
  // TODO: what is the proper way? Here I am simulating close manually :-/
  file_explorer_->closeEvent(event);
  // TODO: is this the proper way, with guessing the proper superclass?
  QMainWindow::closeEvent(event);
}

void MainWindow::setModel(model::Model* model) {
  file_explorer_->setModel(model);
}

void MainWindow::savePersistedState() {
  QSettings settings;
  // TODO: extract key constants
  settings.setValue("layout/main_window/size", size());
  settings.setValue("layout/main_window/pos", pos());
  settings.setValue("layout/main_window/state", saveState());
}

void MainWindow::restorePersistedState() {
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

} // namespace qt_file_explorer::widgets
