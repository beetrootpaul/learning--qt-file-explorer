#ifndef QT_FILE_EXPLORER_SRC_DIRECTORY_PICKER_DIRECTORY_PICKER_WIDGET_H
#define QT_FILE_EXPLORER_SRC_DIRECTORY_PICKER_DIRECTORY_PICKER_WIDGET_H

#import <QFileSystemModel>
#import <QTreeView>

namespace qt_file_explorer {

class DirectoryPickerWidget : public QTreeView {

public:
  DirectoryPickerWidget();

  void setCurrentPath(const QString& path);

private:
  const QString default_path = QDir::homePath();
  QFileSystemModel* model;
};

} // namespace qt_file_explorer

#endif //QT_FILE_EXPLORER_SRC_DIRECTORY_PICKER_DIRECTORY_PICKER_WIDGET_H
