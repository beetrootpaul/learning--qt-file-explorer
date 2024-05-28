#ifndef QT_FILE_EXPLORER_PERSISTED_STATE_PERSISTED_STATE_KEYS_H
#define QT_FILE_EXPLORER_PERSISTED_STATE_PERSISTED_STATE_KEYS_H

namespace qt_file_explorer::persisted_state {

class PersistedStateKeys {
public:
  // The versioned prefix comes handy when working heavily on the persisted
  // state – thanks to it we can simply increment the prefix and in result
  // we get an app in a fresh state, with nothing persisted yet. Alternatively,
  // we can do `settings.remove(PersistedStateKeys.prefix)` and achieve
  // a similar result.
  inline static const std::string prefix = "v15/";

  inline static const std::string groupState = prefix + "state/";
  inline static const std::string groupLayout = prefix + "layout/";
  inline static const std::string groupWindow = prefix + "window/";

  inline static const std::string statePath =
      groupWindow + "state/path";
  inline static const std::string stateViewType =
      groupWindow + "state/view_type";
  inline static const std::string mainWindowSize =
      groupWindow + "main_window/size";
  inline static const std::string mainWindowPos =
      groupWindow + "main_window/pos";
  inline static const std::string mainWindowState =
      groupLayout + "main_window/state";
  inline static const std::string splitterState =
      groupLayout + "splitter/state";
};

} // namespace qt_file_explorer::persisted_state

#endif //QT_FILE_EXPLORER_PERSISTED_STATE_PERSISTED_STATE_KEYS_H
