#
# CMakeLists.txt generated by CLion for a Qt project and managed by CLion as well
#

cmake_minimum_required(VERSION 3.27)
project(learning__qt_file_explorer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Concurrent
        REQUIRED)

add_executable(learning__qt_file_explorer src/main.cc
        src/app_state/app_state.cc
        src/app_state/app_state.h
        src/app_state/dir_listing_view_type.h
        src/app_state/switch_dir_command.cc
        src/app_state/switch_dir_command.h
        src/gui/actions/action_back.cc
        src/gui/actions/action_back.h
        src/gui/actions/action_collapse_all.cc
        src/gui/actions/action_collapse_all.h
        src/gui/actions/action_forward.cc
        src/gui/actions/action_forward.h
        src/gui/actions/action_go_to_downloads.cc
        src/gui/actions/action_go_to_downloads.h
        src/gui/actions/action_go_to_home.cc
        src/gui/actions/action_go_to_home.h
        src/gui/actions/action_reset_layout.cc
        src/gui/actions/action_reset_layout.h
        src/gui/actions/action_toggle_dir_listing_view_type.cc
        src/gui/actions/action_toggle_dir_listing_view_type.h
        src/gui/actions/action_toggle_preview.cc
        src/gui/actions/action_toggle_preview.h
        src/gui/dir_listing/dir_listing_icons_widget.cc
        src/gui/dir_listing/dir_listing_icons_widget.h
        src/gui/dir_listing/dir_listing_list_widget.cc
        src/gui/dir_listing/dir_listing_list_widget.h
        src/gui/dir_listing/dir_listing_shared_model.h
        src/gui/dir_picker/dir_picker_widget.cc
        src/gui/dir_picker/dir_picker_widget.h
        src/gui/main_window.cc
        src/gui/main_window.h
        src/gui/monospace_font.h
        src/gui/preview/file_name_preview_widget.cc
        src/gui/preview/file_name_preview_widget.h
        src/gui/preview/image_preview_widget.cc
        src/gui/preview/image_preview_widget.h
        src/gui/preview/json_preview_widget.cc
        src/gui/preview/json_preview_widget.h
        src/gui/preview/markdown_preview_widget.cc
        src/gui/preview/markdown_preview_widget.h
        src/gui/preview/preview_dock_widget.cc
        src/gui/preview/preview_dock_widget.h
        src/gui/preview/preview_widget.h
        src/gui/preview/text_preview_widget.cc
        src/gui/preview/text_preview_widget.h
        src/gui/toolbar.cc
        src/gui/toolbar.h
        src/logging/message_handler_with_file_output.h
        src/persisted_state/persisted_state_keys.h
        src/persisted_state/with_persisted_state.h
        src/shortcuts.h
)
target_link_libraries(learning__qt_file_explorer
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt6::Concurrent
)

# Manually added part:
#
# QT_NO_DEBUG_OUTPUT makes `qDebug()` do nothing, which is what we want for the Release build.
#
# For more info see:
# - https://stackoverflow.com/a/13494690/1036577
# - https://stackoverflow.com/a/64719718/1036577
target_compile_definitions(learning__qt_file_explorer PRIVATE
        $<$<CONFIG:Release>:
        QT_NO_DEBUG_OUTPUT=1
        >
)
