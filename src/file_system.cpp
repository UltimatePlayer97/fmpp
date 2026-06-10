#include "file_system.hpp"
#include "ui/components/icon/icons.hpp"
#include "utils/formatter.hpp"
#include <cmath>
#include <cstdint>
#include <filesystem>

using namespace std;

FileSystemEngine::FileSystemEngine() {
    string home_env = getenv("HOME") ? getenv("HOME") : ".";
    home_dir = filesystem::absolute(home_env);
    current_dir = home_dir;

    sidebar_paths = {
        home_dir,
        home_dir / "Documents",
        home_dir / "Downloads",
        home_dir / "Desktop"
    };

    update_directory();
}

FileSystemEngine::DiskStats FileSystemEngine::get_root_disk_stats() const {
    DiskStats stats{0, 0, 0.0, false};

    try {
        filesystem::space_info si = filesystem::space("/");

        stats.total_bytes = si.capacity;
        stats.available_bytes = si.available;

        uint64_t used_bytes = si.capacity - si.available;
        if (si.capacity > 0) {
            stats.used_percentage = round((static_cast<double>(used_bytes) / si.capacity) * 100.0);
        }

        stats.is_critical = (stats.used_percentage >= 90.0);

        stats.total_str = Utils::format_bytes(stats.total_bytes);
        stats.used_str = Utils::format_bytes(used_bytes);
    } catch (...) {
        // Fallback defaults are already set above in case this fails
    }
    return stats;
}

void FileSystemEngine::change_directory(const filesystem::path& new_path) {
    current_dir = new_path;
    update_directory();
}

void FileSystemEngine::update_directory() {
    items.clear();
    display_names.clear();

    if (current_dir.has_parent_path() && current_dir != current_dir.root_path()) {
        FileItem parent_item;
        parent_item.name = "../";
        parent_item.path = current_dir.parent_path();
        parent_item.isDirectory = true;
        items.push_back(parent_item);

        string icon = string(get_icon_for_item(parent_item.path, true));
        display_names.push_back(icon + " " + parent_item.name);
    }

    try {
        for (const auto& entry : filesystem::directory_iterator(current_dir)) {
            string filename = entry.path().filename().string();
            if (filename == "." || filename == "..") {
                continue;
            }

            FileItem item;
            item.path = entry.path();
            item.isDirectory = entry.is_directory();
            item.name = filename;
            items.push_back(item);

            string icon = string(get_icon_for_item(item.path, item.isDirectory));
            string display = icon + " " + item.name;

            if (item.isDirectory) {
                display += "/";
            }
            display_names.push_back(display);
        }
    } catch (...) {}
}
