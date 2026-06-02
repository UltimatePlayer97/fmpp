#include <ftxui/dom/elements.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/component.hpp>

#include <iostream>
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
    filesystem::path path = filesystem::current_path();
    cout << "Current path: " << path << endl;

    vector<FileItem> items;
    vector<string> display_names;

    for (const auto& entry : filesystem::directory_iterator(path)) {
        FileItem item;
        item.path = entry.path();
        item.isDirectory = entry.is_directory();
        item.name = item.path.filename().string();
        items.push_back(item);
    }

    for (const auto& item : items) {
        display_names.push_back(item.name);
        if (item.isDirectory) {
            display_names.back() += " (directory)";
        }
    }

    auto screen = ScreenInteractive::TerminalOutput();
    vector<string> entries;
    for (const auto& item : items) {
        entries.push_back(item.name);
    }
    int selected = 0;
    auto menu = Menu(&entries, &selected);
    screen.Loop(menu);


    return 0;
}
