#pragma once

#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <memory>
#include "../file_system.hpp"

using namespace std;
using namespace ftxui;

class BreadcrumbComponent;
class SidebarComponent;
class ContentViewComponent;

class UIComponents {
public:
    UIComponents(ScreenInteractive& screen, FileSystemEngine& engine);
    ~UIComponents();

    Component build_ui_tree();

private:
    ScreenInteractive& screen_;
    FileSystemEngine& engine_;

    unique_ptr<BreadcrumbComponent> breadcrumb_bar_;
    unique_ptr<SidebarComponent> sidebar_panel_;
    unique_ptr<ContentViewComponent> content_view_;
};
