#include "components.hpp"
#include "components/breadcrumb.hpp"
#include "components/sidebar.hpp"
#include "components/content_view.hpp"
#include "ftxui/screen/color.hpp"
#include <ftxui/dom/elements.hpp>
#include <ftxui/component/component.hpp>
#include <memory>
#include <string>

using namespace std;
using namespace ftxui;

UIComponents::UIComponents(ScreenInteractive& screen, FileSystemEngine& engine)
    : screen_(screen), engine_(engine) {

    breadcrumb_bar_ = make_unique<BreadcrumbComponent>();

    sidebar_panel_ = make_unique<SidebarComponent>(engine_.get_sidebar_paths(), [this](const string& path) {
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

    auto disk_click_handler = CatchEvent(Renderer([this]() {
            auto disk = engine_.get_root_disk_stats();
            int rounded_percent = static_cast<int>(disk.used_percentage);

            std::string title_text = " 󰋊  Devices (" + std::to_string(rounded_percent) + "%)";
            std::string size_text = " " + disk.used_str + " / " + disk.total_str;

            float gauge_value = static_cast<float>(disk.used_percentage / 100.0);
            auto progress_bar = gauge(gauge_value);

            if (disk.is_critical) {
                progress_bar = progress_bar | color(Color::Red);
            } else {
                progress_bar = progress_bar | color(Color::Blue);
            }

            auto content = vbox({
                text(title_text) | bold,
                progress_bar | size(HEIGHT, EQUAL, 1),
                text(size_text) | color(Color::GrayDark)
            });
            return content;

        }) | focus,
        [this](Event event) {
            if (event.is_mouse() &&
                event.mouse().button == Mouse::Left &&
                event.mouse().motion == Mouse::Pressed)
            {
                engine_.change_directory("/");
                content_view_->ResetSelection();
                return true;
            }

            if (event == Event::Return) {
                engine_.change_directory("/");
                content_view_->ResetSelection();
                return true;
            }

            return false;
        });

    main_container_ = Container::Horizontal({
        sidebar_panel_->GetControl(),
        content_view_->GetControl(),
        disk_click_handler
    });

    auto resume_button = Button("Resume", [this]() {
        show_escape_menu_ = false;
    });

    auto quit_button = Button("Quit Application", [this]() {
        screen_.ExitLoopClosure()();
    });

    auto escape_menu_buttons = Container::Vertical({
        resume_button,
        quit_button
    });

    auto dynamic_focus_switcher = Container::Tab(
        {main_container_, escape_menu_buttons},
        &show_escape_menu_
    );

    auto master_event_handler = CatchEvent(dynamic_focus_switcher, [this](Event event) {
        if (event == Event::Escape) {
            show_escape_menu_ = !show_escape_menu_;
            return true;
        }
        return false;
    });

    return Renderer(master_event_handler, [this, resume_button, quit_button, disk_click_handler]() {
        breadcrumb_bar_->UpdatePath(engine_.get_current_dir_string());
        auto main_view = vbox({
            breadcrumb_bar_->Render(),
            separator(),
            hbox({
                vbox({
                    text(" Places ") | bold,
                    separator(),
                    sidebar_panel_->GetControl()->Render() | vscroll_indicator | frame,

                    filler(),
                    separator(),
                    disk_click_handler->Render()
                }) | size(WIDTH, EQUAL, 24),
                separator(),
                vbox({
                    text(" Content ") | bold,
                    separator(),
                    content_view_->GetControl()->Render() | vscroll_indicator | frame
                }) | flex
            }) | flex
        }) | flex;

        if (show_escape_menu_) {
            return dbox({
                main_view,
                vbox({
                    text(" ESCAPE MENU ") | bold | center,
                    separator(),
                    vbox({
                        resume_button->Render() | center,
                        text(""),
                        quit_button->Render() | center | color(Color::RedLight)
                    }),
                }) | bgcolor(Color::Black)
                   | border
                   | size(WIDTH, EQUAL, 40)
                   | size(HEIGHT, EQUAL, 11)
                   | center
            });
        }

        return main_view;
    });
}
