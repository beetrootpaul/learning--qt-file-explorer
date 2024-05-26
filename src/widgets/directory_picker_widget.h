#ifndef QT_FILE_EXPLORER_DIRECTORY_PICKER_WIDGET_H
#define QT_FILE_EXPLORER_DIRECTORY_PICKER_WIDGET_H

#import <QFileSystemModel>
#import <QListView>

#include "../app_state/app_state.h"

namespace qt_file_explorer::widgets {

class DirectoryPickerWidget : public QListView {

Q_OBJECT

public:
  void init(const std::shared_ptr<app_state::AppState>& appState);

};

} // namespace qt_file_explorer::widgets

#endif //QT_FILE_EXPLORER_DIRECTORY_PICKER_WIDGET_H
