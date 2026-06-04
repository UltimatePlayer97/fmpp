#include "components.hpp"
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

UIComponents::UIComponents(ScreenInteractive& screen, FileSystemEngine& engine)
    : screen_(screen), engine_(engine) {}

Component UIComponents::create_sidebar_panel() {
    MenuOption sidebar_option;
    sidebar_option.on_enter = [this]() {
        auto paths = engine_.get_sidebar_paths();
        if (selected_sidebar_index_ >= 0 && selected_sidebar_index_ < static_cast<int>(paths.size())) {
            if (std::filesystem::exists(paths[selected_sidebar_index_])) {
                engine_.change_directory(paths[selected_sidebar_index_]);
                display_names_ = engine_.get_display_names();
                selected_file_index_ = 0;
            }
        }
    };
    return Menu(&sidebar_entries_, &selected_sidebar_index_, sidebar_option);
}

Component UIComponents::create_content_panel() {
    MenuOption option;
    option.on_enter = [this]() {
        auto& items = engine_.get_items();
        if (selected_file_index_ >= 0 && selected_file_index_ < (int)items.size()) {
            if (items[selected_file_index_].isDirectory) {
                engine_.change_directory(items[selected_file_index_].path);
                selected_file_index_ = 0;
            }
        }
    };

    return Menu(const_cast<vector<string>*>(&engine_.get_display_names()), &selected_file_index_, option);
}

Component UIComponents::create_escape_modal() {
    MenuOption escape_option;
    escape_option.on_enter = [this]() {
        if (selected_escape_index_ == 0) {
            screen_.ExitLoopClosure()();
        }
    };
    return Menu(&escape_entries_, &selected_escape_index_, escape_option);
}

Component UIComponents::build_ui_tree() {
    auto sidebar_menu = create_sidebar_panel();
    auto menu = create_content_panel();
    auto escape_menu = create_escape_modal();

    auto main_split = Container::Horizontal({
        sidebar_menu,
        menu
    });

    auto main_tabs = Container::Tab({main_split, escape_menu}, &show_escape_menu_);

    auto renderer = Renderer(main_tabs, [=]() {
        auto panel_layout = hbox({
            vbox({
                text(" Places ") | bold | color(Color::Cyan),
                separator(),
                sidebar_menu->Render() | vscroll_indicator | frame
            }) | size(WIDTH, EQUAL, 18),
            separator(),
            vbox({
                text(" Content ") | bold | color(Color::Cyan),
                separator(),
                menu->Render() | vscroll_indicator | frame | flex
            }) | flex
        });

        auto base_window = window(
            text(" File Manager++ | " + engine_.get_current_dir_string()) | bold | color(Color::Blue),
            panel_layout
        );

        if (show_escape_menu_ != 0) {
            return dbox({
                base_window,
                window(text(" Menu ") | bold | color(Color::Red), escape_menu->Render()) | clear_under | center
            });
        }

        return base_window;
    });

    return CatchEvent(renderer, [this](Event event) {
        if (event == Event::Escape) {
            show_escape_menu_ = (show_escape_menu_ == 0) ? 1 : 0;
            return true;
        }
        return false;
    });
}
