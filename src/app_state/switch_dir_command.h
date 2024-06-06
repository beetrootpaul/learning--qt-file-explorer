#ifndef QT_FILE_EXPLORER_APP_STATE_SWITCH_DIR_COMMAND_H
#define QT_FILE_EXPLORER_APP_STATE_SWITCH_DIR_COMMAND_H

#include <QUndoCommand>

#include "app_state.h"

namespace qt_file_explorer::app_state {

class SwitchDirCommand : public QUndoCommand {

public:
  SwitchDirCommand(app_state::AppState* appState, QString oldDir,
                   QString newDir, bool originatedFromDirPicker);
  ~SwitchDirCommand();

  void redo() override;
  void undo() override;

private:
  app_state::AppState* appState_;
  const QString oldDir_;
  const QString newDir_;
  bool originatedFromDirPicker_;
};

} // namespace qt_file_explorer::app_state

#endif //QT_FILE_EXPLORER_APP_STATE_SWITCH_DIR_COMMAND_H
