#ifndef QT_FILE_EXPLORER_SRC_DIRECTORY_PICKER_WIDGET_H
#define QT_FILE_EXPLORER_SRC_DIRECTORY_PICKER_WIDGET_H

#import <QFileSystemModel>
#import <QTreeView>

#include "../model/model.h"

namespace qt_file_explorer::widgets {

class DirectoryPickerWidget : public QTreeView {

public:
  DirectoryPickerWidget();
  void setModel(model::Model* model);

private:
  model::Model* model_;
  QFileSystemModel* file_system_model_;
};

} // namespace qt_file_explorer::widgets

#endif //QT_FILE_EXPLORER_SRC_DIRECTORY_PICKER_WIDGET_H
