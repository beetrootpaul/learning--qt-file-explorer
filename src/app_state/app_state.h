#ifndef QT_FILE_EXPLORER_APP_STATE_APP_STATE_H
#define QT_FILE_EXPLORER_APP_STATE_APP_STATE_H

#include <QDir>
#include <QObject>
#include <QString>

#include "../persisted_state/with_persisted_state.h"
#include "dir_listing_view_type.h"

namespace qt_file_explorer::app_state {

class AppState
    : public QObject,
      public persisted_state::WithPersistedState,
      public QSharedData {

Q_OBJECT

public:
  AppState();
  ~AppState();

  QString currentPath();
  void switchPathToHome();
  void switchPathToDownloads();
  void switchPathTo(const QString& path, bool originatedFromDirPicker = false);

  DirListingViewType currentDirListingViewType();
  void toggleDirListingViewType();

  void savePersistedState() override;
  void loadPersistedState() override;

signals:
  void signalPathChanged(bool originatedFromDirPicker);
  void signalViewTypeChanged();

private:
  const QString homePath_ = QDir::homePath();
  QString currentPath_;
  DirListingViewType currentDirListingViewType_;

  QString downloadsPath();

};

} // namespace qt_file_explorer::app_state

#endif //QT_FILE_EXPLORER_APP_STATE_APP_STATE_H