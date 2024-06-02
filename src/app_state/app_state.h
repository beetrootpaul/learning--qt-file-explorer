#ifndef QT_FILE_EXPLORER_APP_STATE_APP_STATE_H
#define QT_FILE_EXPLORER_APP_STATE_APP_STATE_H

#include <QDir>
#include <QObject>
#include <QString>
#include <QUndoStack>

#include "../persisted_state/with_persisted_state.h"
#include "dir_listing_view_type.h"

namespace qt_file_explorer::app_state {

class AppState
    : public QObject,
      public persisted_state::WithPersistedState,
      public QSharedData {

Q_OBJECT

public:
  AppState(QObject* parent);
  ~AppState();

  QString browsedDir();
  void switchBrowsedDirToHome();
  void switchBrowsedDirToDownloads();
  void
  switchBrowsedDirTo(const QString& dir, bool originatedFromDirPicker = false);

  bool canUndoSwitchBrowsedDir();
  bool canRedoSwitchBrowsedDir();
  void undoSwitchBrowsedDir();
  void redoSwitchBrowsedDir();

  DirListingViewType currentDirListingViewType();
  void toggleDirListingViewType();

  QString selectedPath();
  void switchSelectedPathTo(const QString& path);

  bool isPreviewVisible();
  void togglePreviewVisible();

  void savePersistedState() override;
  void loadPersistedState() override;

  // This "internal" method is meant to be used by QUndoCommand instances
  // in order to directly change AppState.
  void setBrowsedDir(const QString& dir, bool originatedFromDirPicker = false);

signals:
  void signalBrowsedDirChanged(bool originatedFromDirPicker);
  void signalBrowsedDirHistoryUpdated();
  void signalViewTypeChanged();
  void signalSelectedPathChanged();
  void signalPreviewVisibleChanged();

private:
  const QString homeDir_ = QDir::homePath();

  QString browsedDir_ = homeDir_;
  DirListingViewType currentDirListingViewType_ = DirListingViewType::List;
  QString selectedPath_ = "";
  bool isPreviewVisible_ = false;

  QUndoStack undoStack_ = QUndoStack(this);

  QString downloadsDir();

};

} // namespace qt_file_explorer::app_state

#endif //QT_FILE_EXPLORER_APP_STATE_APP_STATE_H
