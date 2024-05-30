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
  inline static const std::string prefix = "v23/";

  // Groups allow us to reset many values at once, e.g. everything
  // that should reset on "Reset layout" action.

  inline static const std::string groupResettableLayout =
      prefix + "resettable_layout/";
  inline static const std::string previewVisible =
      groupResettableLayout + "preview_visible";
  inline static const std::string mainWindowState =
      groupResettableLayout + "main_window_state";
  inline static const std::string splitterState =
      groupResettableLayout + "splitter_state";

  inline static const std::string groupOther = prefix + "other/";
  inline static const std::string mainWindowSize =
      groupOther + "main_window_size";
  inline static const std::string mainWindowPos =
      groupOther + "main_window_pos";
  inline static const std::string browsedDir =
      groupOther + "browsed_dir";
  inline static const std::string listingViewType =
      groupOther + "listing_view_type";
  inline static const std::string listingListHeaderState =
      groupOther + "listing_list_header_state";
};

} // namespace qt_file_explorer::persisted_state

#endif //QT_FILE_EXPLORER_PERSISTED_STATE_PERSISTED_STATE_KEYS_H
