#ifndef QT_FILE_EXPLORER_SRC_FILE_EXPLORER_H
#define QT_FILE_EXPLORER_SRC_FILE_EXPLORER_H

#include <QSplitter>

#include "directory_picker_widget.h"
#include "directory_listing_widget.h"
#include "model.h"

namespace qt_file_explorer::widgets {

class FileExplorer : public QSplitter {

public:
  FileExplorer();

  void closeEvent(QCloseEvent* event) override;

  void setModel(model::Model* model);

private:
  // TODO: Do I need to delete them in the window's destructor?
  DirectoryPickerWidget* directory_picker_;
  DirectoryListingWidget* directory_listing_;

  void savePersistedState();
  void restorePersistedState();
};

} // namespace qt_file_explorer::widgets

#endif //QT_FILE_EXPLORER_SRC_FILE_EXPLORER_H
