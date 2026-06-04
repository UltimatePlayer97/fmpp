#include "content_view.hpp"

using namespace std;
using namespace ftxui;

ContentViewComponent::ContentViewComponent(vector<string>* display_names_ptr, function<void(int)> on_file_enter) {
    MenuOption option;
    option.on_enter = [this, on_file_enter]() {
        on_file_enter(selected_index_);
    };

    menu_ = Menu(display_names_ptr, &selected_index_, option);
}

void ContentViewComponent::ResetSelection() {
    selected_index_ = 0;
}

Component ContentViewComponent::GetControl() {
    return menu_;
}
