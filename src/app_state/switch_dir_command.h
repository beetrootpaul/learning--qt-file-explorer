#ifndef QT_FILE_EXPLORER_APP_STATE_SWITCH_DIR_COMMAND_H
#define QT_FILE_EXPLORER_APP_STATE_SWITCH_DIR_COMMAND_H

#include <QUndoCommand>

#include "app_state.h"

namespace qt_file_explorer::app_state {

class SwitchDirCommand : public QUndoCommand {

public:
  SwitchDirCommand(app_state::AppState* appState, QString oldDir,
                   QString newDir, bool originatedFromDirPicker)
      : appState_(appState), oldDir_(oldDir), newDir_(newDir),
        originatedFromDirPicker_(originatedFromDirPicker) {
    qDebug() << "+ SwitchDirCommand" << this;
  };

  ~SwitchDirCommand() {
    qDebug() << "~ SwitchDirCommand" << this;
  };

  void redo() override {
    appState_->setBrowsedDir(newDir_, originatedFromDirPicker_);
    // After the command is run for the first time (which really might be originated
    // from the picker), the next runs are no longer originated from the picker.
    originatedFromDirPicker_ = false;
  };

  void undo() override {
    appState_->setBrowsedDir(oldDir_, /*originatedFromDirPicker_=*/false);
  };

private:
  app_state::AppState* appState_;
  const QString oldDir_;
  const QString newDir_;
  bool originatedFromDirPicker_;
};

} // namespace qt_file_explorer::app_state

#endif //QT_FILE_EXPLORER_APP_STATE_SWITCH_DIR_COMMAND_H
