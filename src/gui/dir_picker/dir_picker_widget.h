#ifndef QT_FILE_EXPLORER_DIR_PICKER_DIR_PICKER_WIDGET_H
#define QT_FILE_EXPLORER_DIR_PICKER_DIR_PICKER_WIDGET_H

#include <QFileSystemModel>
#include <QTreeView>

#include "../../app_state/app_state.h"

namespace qt_file_explorer::gui {

class DirPickerWidget : public QTreeView {

Q_OBJECT

public:
  DirPickerWidget();
  ~DirPickerWidget();

  void init(app_state::AppState* appState);

private:
  app_state::AppState* appState_;
  QFileSystemModel* model_ = nullptr;

  void keyPressEvent(QKeyEvent* event) override;

  void openDir(const QModelIndex& index);

private slots:
  void slotBrowsedDirChanged(bool originatedFromDirPicker);

};

} // namespace qt_file_explorer::gui

#endif //QT_FILE_EXPLORER_DIR_PICKER_DIR_PICKER_WIDGET_H
