#pragma once

#include <filesystem>
#include <ftxui/component/component.hpp>
#include <string>
#include <vector>
#include <functional>

using namespace std;
using namespace ftxui;

class SidebarComponent {
public:
    SidebarComponent(const vector<filesystem::path>& system_paths,
                         function<void(const string&)> on_place_selected);

    Component GetControl();

private:
    int selected_index_ = 0;
    vector<string> places_ = {"Home", "Root", "Documents", "Downloads"};
    vector<std::filesystem::path> targets_;
    Component menu_;
};
