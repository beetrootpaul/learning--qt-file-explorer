#ifndef QT_FILE_EXPLORER_DIR_PICKER_DIR_PICKER_WIDGET_H
#define QT_FILE_EXPLORER_DIR_PICKER_DIR_PICKER_WIDGET_H

#include <QFileSystemModel>
#include <QTreeView>

#include "../../app_state/app_state.h"

namespace qt_file_explorer::widgets {

class DirPickerWidget : public QTreeView {

Q_OBJECT

public:
  DirPickerWidget();
  ~DirPickerWidget();

  void init(const QSharedPointer<app_state::AppState>& appState);

private:
  QSharedPointer<app_state::AppState> appState_;
  QFileSystemModel* model_ = nullptr;

  void keyPressEvent(QKeyEvent* event) override;

  void openDir(const QModelIndex& index);

  // TODO: write down concepts in README, like "browsed dir", "selected path"

private slots:
  void slotBrowsedDirChanged(bool originatedFromDirPicker);

};

} // namespace qt_file_explorer::widgets

#endif //QT_FILE_EXPLORER_DIR_PICKER_DIR_PICKER_WIDGET_H
