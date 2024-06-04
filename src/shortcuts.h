#ifndef QT_FILE_EXPLORER_SHORTCUTS_H
#define QT_FILE_EXPLORER_SHORTCUTS_H

#include <QKeySequence>

namespace qt_file_explorer {

struct Shortcuts {

  // NOTE: The constants below are functions and not fields, because
  // `inline static const QKeySequence back = QKeySequence::Back`
  // was causing
  // `Process finished with exit code 139 (interrupted by signal 11:SIGSEGV)`
  // on the very app start.

  inline static QKeySequence back() { return QKeySequence::Back; }

  inline static QKeySequence forward() { return QKeySequence::Forward; }

  inline static QKeySequence goToDownloads() { return Qt::META | Qt::Key_D; }

  inline static QKeySequence goToHome() { return Qt::META | Qt::Key_H; }

  inline static QKeySequence toggleDirListingViewType() {
    return Qt::META | Qt::Key_V;
  }

  inline static QKeySequence togglePreview() { return Qt::META | Qt::Key_P; }

  inline static QKeySequence resetLayout() { return Qt::META | Qt::Key_R; }

};

} // namespace qt_file_explorer

#endif //QT_FILE_EXPLORER_SHORTCUTS_H
