#ifndef QT_FILE_EXPLORER_GUI_ACTIONS_ACTION_GO_TO_DOWNLOADS_H
#define QT_FILE_EXPLORER_GUI_ACTIONS_ACTION_GO_TO_DOWNLOADS_H

#include <QAction>
#include <QObject>

#include "../../app_state/app_state.h"

namespace qt_file_explorer::gui {

class ActionGoToDownloads : public QAction {

Q_OBJECT

public:
  ActionGoToDownloads(QObject* parent,
                      const QSharedPointer<app_state::AppState>& appState);
  ~ActionGoToDownloads();

private:

  QSharedPointer<app_state::AppState> appState_;

private slots:
  void perform();

};

} // namespace qt_file_explorer::gui

#endif //QT_FILE_EXPLORER_GUI_ACTIONS_ACTION_GO_TO_DOWNLOADS_H