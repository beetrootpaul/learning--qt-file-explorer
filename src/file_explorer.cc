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
  setStretchFactor(0, 1);
  addWidget(directory_listing_);
  setStretchFactor(1, 2);

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
  if (!state.isEmpty()) {
    restoreState(state);
  } else {
    int stretch_total = 0;
    for (int i = 0; i < count(); ++i) {
      stretch_total += widget(i)->sizePolicy().horizontalStretch();
    }

    auto desired_sizes = QList<int>(count());
    int desired_widths_accumulated = 0;
    for (int i = 0; i < count(); ++i) {
      float ratio =
          (static_cast<float>(widget(i)->sizePolicy().horizontalStretch())) /
          (static_cast<float>(stretch_total));
      int desired_width = i < (count() - 1)
                          ? static_cast<int>(std::floor(
              (static_cast<float>(width()) * ratio)))
                          : width() - desired_widths_accumulated;
      desired_widths_accumulated += desired_width;
      desired_sizes[i] = desired_width;
    }
    setSizes(desired_sizes);
  }
}

} // namespace qt_file_explorer::widgets
