#include "file_system.hpp"

FileSystemEngine::FileSystemEngine() {
    std::string home_env = getenv("HOME") ? getenv("HOME") : ".";
    home_dir = std::filesystem::absolute(home_env);
    current_dir = home_dir;

    sidebar_paths = {
        home_dir,
        home_dir / "Documents",
        home_dir / "Downloads",
        home_dir / "Desktop"
    };

    update_directory();
}

void FileSystemEngine::change_directory(const std::filesystem::path& new_path) {
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
        display_names.push_back("../");
    }

    try {
        for (const auto& entry : std::filesystem::directory_iterator(current_dir)) {
            std::string filename = entry.path().filename().string();
            if (filename == "." || filename == "..") {
                continue;
            }

            FileItem item;
            item.path = entry.path();
            item.isDirectory = entry.is_directory();
            item.name = filename;
            items.push_back(item);

            std::string display = item.name;
            if (item.isDirectory) {
                display += "/";
            }
            display_names.push_back(display);
        }
    } catch (...) {}
}
