#ifndef QT_FILE_EXPLORER_WITH_PERSISTED_STATE_H
#define QT_FILE_EXPLORER_WITH_PERSISTED_STATE_H

namespace qt_file_explorer {

class WithPersistedState {

public:
  virtual void savePersistedState() = 0;
  virtual void loadPersistedState() = 0;

};

} // namespace qt_file_explorer

#endif //QT_FILE_EXPLORER_WITH_PERSISTED_STATE_H
