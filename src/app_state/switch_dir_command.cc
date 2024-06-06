#include "switch_dir_command.h"

namespace qt_file_explorer::app_state {

SwitchDirCommand::SwitchDirCommand(app_state::AppState* appState,
                                   QString oldDir, QString newDir,
                                   bool originatedFromDirPicker) :
    appState_(appState), oldDir_(oldDir), newDir_(newDir),
    originatedFromDirPicker_(originatedFromDirPicker) {
  qDebug() << "+ SwitchDirCommand" << this;
};

SwitchDirCommand::~SwitchDirCommand() {
  qDebug() << "~ SwitchDirCommand" << this;
};

void SwitchDirCommand::redo() {
  appState_->
      setBrowsedDir(newDir_, originatedFromDirPicker_
  );
  // After the command is run for the first time (which really might be originated
  // from the picker), the next runs are no longer originated from the picker.
  originatedFromDirPicker_ = false;
};

void SwitchDirCommand::undo() {
  appState_->
      setBrowsedDir(oldDir_, /*originatedFromDirPicker_=*/false);
}

} // namespace qt_file_explorer::app_state
