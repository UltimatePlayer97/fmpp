#pragma once

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include "file_system.hpp"

using namespace ftxui;

class UIComponents {
public:
    UIComponents(ScreenInteractive& screen, FileSystemEngine& engine);
    Component build_ui_tree();

private:
    ScreenInteractive& screen_;
    FileSystemEngine& engine_;

    int selected_file_index_ = 0;
    int selected_sidebar_index_ = 0;
    int selected_escape_index_ = 0;
    int show_escape_menu_ = 0;

    std::vector<std::string> display_names_;
    std::vector<std::string> sidebar_entries_ = {"Home", "Documents", "Downloads", "Desktop"};
    std::vector<std::string> escape_entries_ = {"Quit"};

    Component content_menu_;
    Component create_sidebar_panel();
    Component create_content_panel();
    Component create_escape_modal();
};
