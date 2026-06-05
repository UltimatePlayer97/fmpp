#include "sidebar.hpp"
#include <ftxui/component/component_options.hpp>

using namespace std;
using namespace ftxui;

SidebarComponent::SidebarComponent(const vector<filesystem::path>& system_paths, function<void(const string&)> on_place_selected) {
    targets_ = system_paths;

    if (targets_.size() >= 4) {
        targets_.insert(targets_.begin() + 1, filesystem::path("/"));
    }

    MenuOption option;
    option.on_enter = [this, on_place_selected]() {
        if (selected_index_ >= 0 && selected_index_ < static_cast<int>(places_.size())) {
            string actual_target_path = targets_[selected_index_].string();
            on_place_selected(actual_target_path);
        }
    };

    menu_ = Menu(&places_, &selected_index_, option);
}

Component SidebarComponent::GetControl() {
    return menu_;
}
