#pragma once

#include <ftxui/component/component.hpp>
#include <string>

class BreadcrumbComponent {
public:
    BreadcrumbComponent() = default;

    void UpdatePath(const std::string& current_path);

    ftxui::Element Render();

private:
    std::string current_path_;
};
