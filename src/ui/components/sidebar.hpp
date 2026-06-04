#pragma once
#include <ftxui/component/component.hpp>
#include <string>
#include <vector>
#include <functional>

using namespace std;
using namespace ftxui;

class SidebarComponent {
public:
    SidebarComponent(std::function<void(const std::string&)> on_place_selected);

    Component GetControl();

private:
    int selected_index_ = 0;
    vector<string> places_ = {"Home", "Root", "Documents", "Downloads"};
    Component menu_;
};
