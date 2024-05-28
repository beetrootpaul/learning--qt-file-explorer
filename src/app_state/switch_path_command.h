#ifndef QT_FILE_EXPLORER_APP_STATE_SWITCH_PATH_COMMAND_H
#define QT_FILE_EXPLORER_APP_STATE_SWITCH_PATH_COMMAND_H

#include <QUndoCommand>

#include "app_state.h"

namespace qt_file_explorer::app_state {

class SwitchPathCommand : public QUndoCommand {

public:
  SwitchPathCommand(app_state::AppState* appState, QString oldPath,
                    QString newPath, bool originatedFromDirPicker)
      : appState_(appState), oldPath_(oldPath), newPath_(newPath),
        originatedFromDirPicker_(originatedFromDirPicker) {
    qDebug() << "+ SwitchPathCommand" << this;
  };

  ~SwitchPathCommand() {
    qDebug() << "~ SwitchPathCommand" << this;
  };

  void redo() override {
    appState_->setPath(newPath_, originatedFromDirPicker_);
    // After the command is run for the first time (which really might be originated
    // from the picker), the next runs are no longer originated from the picker.
    originatedFromDirPicker_ = false;
  };

  // TODO: what if the dir name changed or dir no longer exist?
  void undo() override {
    appState_->setPath(oldPath_, /*originatedFromDirPicker_=*/false);
  };

private:
  app_state::AppState* appState_;
  const QString oldPath_;
  const QString newPath_;
  bool originatedFromDirPicker_;
};

} // namespace qt_file_explorer::app_state

#endif //QT_FILE_EXPLORER_APP_STATE_SWITCH_PATH_COMMAND_H
