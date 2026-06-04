#pragma once

#include <ftxui/component/component.hpp>
#include <vector>
#include <string>
#include <functional>

using namespace std;
using namespace ftxui;

class ContentViewComponent {
public:
    ContentViewComponent(vector<string>* display_names_ptr, function<void(int)> on_file_enter);

    void ResetSelection();
    Component GetControl();

private:
    int selected_index_ = 0;
    Component menu_;
};
