#ifndef QT_FILE_EXPLORER_SRC_DIRECTORY_PICKER_WIDGET_H
#define QT_FILE_EXPLORER_SRC_DIRECTORY_PICKER_WIDGET_H

#import <QFileSystemModel>
#import <QTreeView>

namespace qt_file_explorer::widgets {

class DirectoryPickerWidget : public QTreeView {

public:
  DirectoryPickerWidget();
  void setCurrentPath(const QString& path);

private:
  const QString default_path_ = QDir::homePath();
  QFileSystemModel* model_;
};

} // namespace qt_file_explorer::widgets

#endif //QT_FILE_EXPLORER_SRC_DIRECTORY_PICKER_WIDGET_H
