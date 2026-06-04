#include "breadcrumb.hpp"
#include <filesystem>
#include <ftxui/dom/elements.hpp>

using namespace std;
using namespace ftxui;

void BreadcrumbComponent::UpdatePath(const std::string& current_path) {
    current_path_ = current_path;
}

Element BreadcrumbComponent::Render() {
    filesystem::path p(current_path_);
    vector<Element> breadcrumbs;
    bool is_first = true;

    for (const auto& part : p) {
        if (part.empty() || part == "/") continue;

        if (!is_first) {
            breadcrumbs.push_back(text(" ❯ ") | color(Color::GrayDark));
        }

        if (part == p.filename()) {
            breadcrumbs.push_back(text(part.string()) | bold | color(Color::White));
        } else {
            breadcrumbs.push_back(text(part.string()) | color(Color::GrayLight));
        }
        is_first = false;
    }

    if (breadcrumbs.empty()) {
        breadcrumbs.push_back(text(" / ") | bold | color(Color::White));
    }

    return hbox(std::move(breadcrumbs))
           | border
           | color(Color::BlueLight);
}
