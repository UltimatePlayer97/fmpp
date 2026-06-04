#include "ftxui/component/component_options.hpp"
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>

#include <filesystem>
#include <string>
#include <vector>

using namespace std;
using namespace ftxui;

struct FileItem {
    string name;
    filesystem::path path;
    bool isDirectory;
};

int main() {
    vector<FileItem> items;
    vector<string> display_names;

    auto screen = ScreenInteractive::TerminalOutput();

    int selected = 0;
    bool should_run = true;
    bool show_escape_menu = false;

    std::filesystem::path current_dir = std::filesystem::current_path();

    auto update_directory = [&]() {
        items.clear();
        display_names.clear();

        if (current_dir.has_parent_path() && current_dir != current_dir.root_path()) {
            FileItem parent_item;
            parent_item.name = "../";
            parent_item.path = current_dir.parent_path();
            parent_item.isDirectory = true;
            items.push_back(parent_item);
            display_names.push_back("../");
        }

        for (const auto& entry : filesystem::directory_iterator(current_dir)) {
            string filename = entry.path().filename().string();
            if (filename == "." || filename == "..") {
                continue;
            }

            FileItem item;
            item.path = entry.path();
            item.isDirectory = entry.is_directory();
            item.name = filename;
            items.push_back(item);

            string display = item.name;
            if (item.isDirectory) {
                display += "/";
            }
            display_names.push_back(display);
        }
    };

    update_directory();

    MenuOption option;
    option.on_enter = [&]() {
        if (selected >= 0 && selected < static_cast<int>(items.size())) {
            if (items[selected].isDirectory) {
                current_dir = items[selected].path;
                update_directory();
                selected = 0;
            }
        }
    };

    auto menu = Menu(&display_names, &selected, option);

    int escape_selected = 0;
    vector<string> escape_entries = {"Quit"};
    MenuOption escape_option;
    escape_option.on_enter = [&]() {
        if (escape_selected == 0) {
            should_run = false;
            screen.ExitLoopClosure()();
        }
    };
    auto escape_menu = Menu(&escape_entries, &escape_selected, escape_option);

    auto renderer = Renderer(Container::Tab({menu, escape_menu}, (int*)&show_escape_menu), [&]() {
        auto base_window = window(
            text(" File Manager++ | " + current_dir.string()) | bold | color(Color::Blue),
            menu->Render()
        );

        if (show_escape_menu) {
            return dbox({
                base_window,
                window(text(" Menu ") | bold | color(Color::Red), escape_menu->Render()) | clear_under | center
            });
        }

        return base_window;
    });

    auto final_component = CatchEvent(renderer, [&](Event event) {
        if (event == Event::Escape) {
            show_escape_menu = !show_escape_menu;
            return true;
        }
        return false;
    });

    screen.Loop(final_component);

    return 0;
}
