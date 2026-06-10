#include <ftxui/component/screen_interactive.hpp>
#include "file_system.hpp"
#include "ui/components.hpp"

int main() {
    auto screen = ftxui::ScreenInteractive::TerminalOutput();
    FileSystemEngine engine;
    UIComponents ui(screen, engine);
    auto app_tree = ui.build_ui_tree();

    screen.Loop(app_tree | xflex | yflex);

    return 0;
}
