#pragma once

#include <filesystem>
#include <string>
#include <vector>

using namespace std;

struct FileItem {
    string name;
    filesystem::path path;
    bool isDirectory;
};

class FileSystemEngine {
public:
    FileSystemEngine();

    void update_directory();
    void change_directory(const filesystem::path& new_path);

    const vector<FileItem>& get_items() const { return items; }
    const vector<string>& get_display_names() const { return display_names; }
    string get_current_dir_string() const { return current_dir.string(); }

    const vector<filesystem::path>& get_sidebar_paths() const { return sidebar_paths; }

private:
    filesystem::path home_dir;
    filesystem::path current_dir;
    vector<FileItem> items;
    vector<string> display_names;
    vector<filesystem::path> sidebar_paths;
};
