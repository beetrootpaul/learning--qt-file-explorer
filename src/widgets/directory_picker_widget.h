#ifndef QT_FILE_EXPLORER_DIRECTORY_PICKER_WIDGET_H
#define QT_FILE_EXPLORER_DIRECTORY_PICKER_WIDGET_H

#import <QFileSystemModel>
#import <QTreeView>

#include "../app_state/app_state.h"

namespace qt_file_explorer::widgets {

class DirectoryPickerWidget : public QTreeView {

Q_OBJECT

public:
  DirectoryPickerWidget();
  ~DirectoryPickerWidget();

  void init(const QSharedPointer<app_state::AppState>& appState);

private:
  QSharedPointer<app_state::AppState> appState_;
  QFileSystemModel* model_ = nullptr;

private slots:
  void slotPathChanged(bool originatedFromDirPicker);
  void currentChanged(const QModelIndex& current,
                      const QModelIndex& previous) override;

};

} // namespace qt_file_explorer::widgets

#endif //QT_FILE_EXPLORER_DIRECTORY_PICKER_WIDGET_H
