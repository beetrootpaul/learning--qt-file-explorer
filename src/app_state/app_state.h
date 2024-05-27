#ifndef QT_FILE_EXPLORER_APP_STATE_APP_STATE_H
#define QT_FILE_EXPLORER_APP_STATE_APP_STATE_H

#include <QDir>
#include <QObject>
#include <QString>

#include "../with_persisted_state.h"
#include "dir_listing_view_type.h"

namespace qt_file_explorer::app_state {

class AppState : public QObject, public WithPersistedState {

Q_OBJECT

public:
  AppState();
  ~AppState();

  QString currentPath();
  void switchPathToHome();
  void switchPathToDownloads();

  DirListingViewType currentDirListingViewType();
  void toggleDirListingViewType();

  void savePersistedState() override;
  void loadPersistedState() override;

signals:
  void signalChanged();

private:
  const QString homePath_ = QDir::homePath();
  QString currentPath_;
  DirListingViewType currentDirListingViewType_;

  QString downloadsPath();

};

} // namespace qt_file_explorer::app_state

#endif //QT_FILE_EXPLORER_APP_STATE_APP_STATE_H
