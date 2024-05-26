#include "main_window.h"

#include <iostream>

#include <QApplication>
#include <QPushButton>
#include <QScreen>
#include <QSettings>
#include <QToolBar>

#include "file_explorer.h"

namespace qt_file_explorer::widgets {

// TODO: should I use constructor for all of this? There is the warning abut model_ not being initialized
MainWindow::MainWindow() {
  setWindowTitle("Qt File Explorer");

  file_explorer_ = new FileExplorer();
  setCentralWidget(file_explorer_);

  // TODO: tabbing order

  // TODO: shortcut. The `&H` does not work, apparently
  auto* quick_open_home_button = new QPushButton("Quick open: &Home");
  QObject::connect(quick_open_home_button, &QPushButton::clicked, [=]() {
    model_->switchPathToHome();
  });
  // TODO: shortcut. The `&D` does not work, apparently
  auto* quick_open_downloads_button = new QPushButton("Quick open: &Downloads");
  QObject::connect(quick_open_downloads_button, &QPushButton::clicked, [=]() {
    model_->switchPathToDownloads();
  });

  // TODO: shortcut. The `&R` does not work, apparently
  auto* reset_layout_button = new QPushButton("&Reset layout");
  QObject::connect(reset_layout_button, &QPushButton::clicked, [=]() {
    QSettings settings;
    settings.remove("layout");
    settings.remove("window");
    // TODO: misleading naming
    restorePersistedState(/*layoutOnly=*/true);
    // TODO: this does not work
    // TODO: conceptually if I had many widgets to reset, nested deeply, I would have keep a reference to each of them :-/
    file_explorer_->restorePersistedState();
  });

  // TODO: extract?
  // TODO: shortcut. The `&S` does not work, apparently
  toggle_dir_listing_view_type_ = new QPushButton("(placeholder)");
  QObject::connect(toggle_dir_listing_view_type_, &QPushButton::clicked, [=]() {
    model_->setDirListingViewType(
        model_->currentDirListingViewType() == model::DirListingViewType::List
        ? model::DirListingViewType::Icons : model::DirListingViewType::List);
  });

  auto* toolbar = new QToolBar();
  toolbar->setObjectName("main_toolbar");
  toolbar->addWidget(quick_open_home_button);
  toolbar->addWidget(quick_open_downloads_button);
  toolbar->addWidget(reset_layout_button);
  toolbar->addWidget(toggle_dir_listing_view_type_);

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
  model_ = model;
  file_explorer_->setModel(model);

  QObject::connect(model_, &model::Model::changed, [=]() {
    toggle_dir_listing_view_type_->setText(
        model_->currentDirListingViewType() ==
        model::DirListingViewType::List
        ? "&Switch to icons" : "&Switch to list");
  });
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
      std::cout << "size is NOT null" << std::endl;
      resize(size);
    } else {
      std::cout << "size IS null" << std::endl;
      resize(800, 600);
    }

    const auto pos = settings.value("window/main_window/pos").toPoint();
    if (!pos.isNull()) {
      std::cout << "pos is NOT null" << std::endl;
      // TODO: make it always visible even if screen size decreases
      move(pos);
    } else {
      std::cout << "pos IS null" << std::endl;
      int desired_pos_x =
          (screen()->availableGeometry().width() - width()) / 2;
      int desired_pos_y =
          (screen()->availableGeometry().height() - height()) / 2;
      move(desired_pos_x, desired_pos_y);
    }
  }

  const auto state = settings.value("layout/main_window/state").toByteArray();
  if (!state.isEmpty()) {
    restoreState(state);
  }
}

} // namespace qt_file_explorer::widgets
