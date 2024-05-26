#include "file_explorer.h"

#include <iostream>

#include <QSettings>

#include "model.h"

namespace qt_file_explorer::widgets {

FileExplorer::FileExplorer() {
  directory_picker_ = new DirectoryPickerWidget();
  directory_listing_ = new DirectoryListingWidget();

  setOrientation(Qt::Orientation::Horizontal);
  addWidget(directory_picker_);
  addWidget(directory_listing_);

  restorePersistedState();
}

void FileExplorer::closeEvent(QCloseEvent* event) {
  std::cout << "close explorer ?!?!" << std::endl;
  savePersistedState();
  // TODO: is this the proper way, with guessing the proper superclass?
  QSplitter::closeEvent(event);
}

void FileExplorer::setModel(model::Model* model) {
  directory_picker_->setCurrentPath(model->currentPath());
  directory_listing_->setCurrentPath(model->currentPath());
}

void FileExplorer::savePersistedState() {
  QSettings settings;
  // TODO: extract key constants
  settings.setValue("layout/file_explorer/state", saveState());
}

void FileExplorer::restorePersistedState() {
  QSettings settings;

  const auto state = settings.value("layout/file_explorer/state",
                                    QByteArray()).toByteArray();
  if (state.isEmpty()) {
    std::cout << "H E R E" << std::endl;
    auto policy = directory_picker_->sizePolicy();
    policy.setHorizontalStretch(1);
    directory_picker_->setSizePolicy(policy);
    policy = directory_listing_->sizePolicy();
    policy.setHorizontalStretch(2);
    directory_listing_->setSizePolicy(policy);
  } else {
    restoreState(state);
  }
}

} // namespace qt_file_explorer::widgets
