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

  // TODO: shortcut
  // TODO: tab order
  auto* resetLayoutButton = new QPushButton("&Reset layout");
  QObject::connect(resetLayoutButton, &QPushButton::clicked, [=]() {
    QSettings settings;
    settings.remove("layout");
    // TODO: misleading naming
    restorePersistedState(/*layoutOnly=*/true);
    // TODO: this does not work
    // TODO: conceptually if I had many widgets to reset, nested deeply, I would have keep a reference to each of them :-/
    file_explorer_->restorePersistedState();
  });

  auto* toolbar = new QToolBar();
  toolbar->setObjectName("main_toolbar");
  toolbar->addWidget(resetLayoutButton);

  toolbar->setMovable(false);
  toolbar->setFloatable(false);

  // Remove context menu in order to remove the ability to close this toolbar
  toolbar->setContextMenuPolicy(Qt::ContextMenuPolicy::PreventContextMenu);

  addToolBar(toolbar);

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
  settings.setValue("window/main_window/size", size());
  settings.setValue("window/main_window/pos", pos());
  settings.setValue("layout/main_window/state", saveState());
}

// TODO: not nice design with this layoutOnly flag :-/
void MainWindow::restorePersistedState(bool layoutOnly) {
  QSettings settings;

  if (!layoutOnly) {
    const auto size = settings.value("window/main_window/size").toSize();
    if (!size.isEmpty()) {
      resize(size);
    } else {
      resize(800, 600);
    }

    const auto pos = settings.value("window/main_window/pos").toPoint();
    if (!pos.isNull()) {
      // TODO: make it always visible even if screen size decreases
      move(pos);
    } else {
      // TODO: make it centered
      move(10, 10);
    }
  }

  const auto state = settings.value("layout/main_window/state",
                                    QByteArray()).toByteArray();
  if (!state.isEmpty()) {
    restoreState(state);
  }
}

} // namespace qt_file_explorer::widgets
