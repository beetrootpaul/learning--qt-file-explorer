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
  inline static const std::string prefix = "v22/";

  // Groups allow us to reset many values at once, e.g. everything
  // that should reset on "Reset layout" action.

  inline static const std::string groupLayout = prefix + "layout/";
  inline static const std::string previewVisible =
      groupLayout + "preview_visible";
  inline static const std::string mainWindowState =
      groupLayout + "main_window_state";
  inline static const std::string splitterState =
      groupLayout + "splitter_state";

  inline static const std::string groupState = prefix + "state/";
  inline static const std::string browsedDir =
      groupState + "browsed_dir";
  inline static const std::string viewType =
      groupState + "view_type";

  inline static const std::string groupWindow = prefix + "window/";
  inline static const std::string mainWindowSize =
      groupWindow + "main_window_size";
  inline static const std::string mainWindowPos =
      groupWindow + "main_window_pos";
};

} // namespace qt_file_explorer::persisted_state

#endif //QT_FILE_EXPLORER_PERSISTED_STATE_PERSISTED_STATE_KEYS_H
