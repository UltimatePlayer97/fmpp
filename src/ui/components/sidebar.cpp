#include "sidebar.hpp"
#include <ftxui/component/component_options.hpp>

using namespace std;
using namespace ftxui;

SidebarComponent::SidebarComponent(const vector<filesystem::path>& system_paths,
                                     function<void(const string&)> on_place_selected) {
    MenuOption option;
    option.on_enter = [this, on_place_selected]() {
        if (selected_index_ >= 0 && selected_index_ < static_cast<int>(places_.size())) {
            string target_path = "/";
            if (places_[selected_index_] == "Home") target_path = "/home";

            on_place_selected(target_path);
        }
    };

    menu_ = Menu(&places_, &selected_index_, option);
}

Component SidebarComponent::GetControl() {
    return menu_;
}
