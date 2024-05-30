#ifndef QT_FILE_EXPLORER_GUI_ACTIONS_ACTION_QUICK_OPEN_DOWNLOADS_H
#define QT_FILE_EXPLORER_GUI_ACTIONS_ACTION_QUICK_OPEN_DOWNLOADS_H

#include <QAction>
#include <QObject>

#include "../../app_state/app_state.h"

namespace qt_file_explorer::gui {

class ActionQuickOpenDownloads : public QAction {

Q_OBJECT

public:
  ActionQuickOpenDownloads(QObject* parent,
                           const QSharedPointer<app_state::AppState>& appState);
  ~ActionQuickOpenDownloads();

private:

  QSharedPointer<app_state::AppState> appState_;

private slots:
  void perform();

};

} // namespace qt_file_explorer::gui

#endif //QT_FILE_EXPLORER_GUI_ACTIONS_ACTION_QUICK_OPEN_DOWNLOADS_H
