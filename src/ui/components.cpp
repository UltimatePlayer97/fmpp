#include "components.hpp"
#include "components/breadcrumb.hpp"
#include "components/sidebar.hpp"
#include "components/content_view.hpp"
#include <ftxui/dom/elements.hpp>

using namespace std;
using namespace ftxui;

UIComponents::UIComponents(ScreenInteractive& screen, FileSystemEngine& engine)
    : screen_(screen), engine_(engine) {

    breadcrumb_bar_ = make_unique<BreadcrumbComponent>();

    sidebar_panel_ = make_unique<SidebarComponent>([this](const string& path) {
        engine_.change_directory(path);
        content_view_->ResetSelection();
    });

    auto* display_vector = const_cast<vector<string>*>(&engine_.get_display_names());

    content_view_ = make_unique<ContentViewComponent>(display_vector, [this](int selected_idx) {
        auto items = engine_.get_items();
        if (selected_idx >= 0 && selected_idx < static_cast<int>(items.size())) {
            if (items[selected_idx].isDirectory) {
                engine_.change_directory(items[selected_idx].path);
                content_view_->ResetSelection();
            }
        }
    });
}

UIComponents::~UIComponents() = default;

Component UIComponents::build_ui_tree() {
    auto container = Container::Horizontal({
        sidebar_panel_->GetControl(),
        content_view_->GetControl()
    });

    return Renderer(container, [this]() {
        breadcrumb_bar_->UpdatePath(engine_.get_current_dir_string());

        return vbox({
            breadcrumb_bar_->Render(),
            separator(),
            hbox({
                vbox({
                    text(" Places ") | bold,
                    separator(),
                    sidebar_panel_->GetControl()->Render() | vscroll_indicator | frame
                }) | size(WIDTH, EQUAL, 18),

                separator(),

                vbox({
                    text(" Content ") | bold,
                    separator(),
                    content_view_->GetControl()->Render() | vscroll_indicator | frame | flex
                }) | flex
            }) | flex
        }) | flex;
    });
}
