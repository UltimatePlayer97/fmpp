#include "ftxui/component/component_options.hpp"
#include "ftxui/screen/color.hpp"
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

    filesystem::path current_dir = std::filesystem::current_path();

    while (should_run) {
        items.clear();
        display_names.clear();

        if (current_dir.has_parent_path() && current_dir != current_dir.root_path()) {
            FileItem parent_item;
            parent_item.path = current_dir.parent_path();
            parent_item.isDirectory = true;
            parent_item.name = "../";
            items.push_back(parent_item);
            display_names.push_back(parent_item.name);
        }

        for (const auto& entry : filesystem::directory_iterator(current_dir)) {
            FileItem item;
            item.path = entry.path();
            item.isDirectory = entry.is_directory();
            item.name = item.path.filename().string();
            items.push_back(item);

            string display = item.name;
            if (item.isDirectory) {
                display += "/";
            }
            display_names.push_back(display);
        }

        MenuOption option;
        option.on_enter = [&]() {
            if (selected >= 0 && selected < items.size()) {
                if (items[selected].isDirectory) {
                    current_dir = items[selected].path;
                    screen.ExitLoopClosure()();
                } else {
                    should_run = false;
                    screen.ExitLoopClosure()();
                }
            }
        };

        auto menu = Menu(&display_names, &selected, option);

        auto renderer = Renderer(menu, [&]() {
            return  window(
                text("File Manager++ | " + current_dir.string()) | bold | color(Color::Blue),
                menu->Render());
        });
        screen.Loop(renderer);

        if (!should_run) {
            break;
        }

        selected = 0;
    }

    return 0;
}
