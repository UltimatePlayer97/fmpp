<img width="1376" height="768" alt="banner" src="https://github.com/user-attachments/assets/402f3e4c-1615-4397-93cd-0491066aa17f" />

# FileManager++

[![Language](https://img.shields.io/badge/language-C%2B%2B17-blue.svg)](https://en.cppreference.com/w/cpp/17)

---
 
A terminal file manager built to make navigation instant and distraction-free. No mouse required.
 
## Quick Start
Head over to [Releases](https://github.com/UltimatePlayer97/fmpp/releases) to download now!
 
## Features
 
- **Dual-panel layout** — a Places sidebar alongside a dynamic directory view for fast context switching
- **Keyboard-first** — navigate, dive into paths, and manage files without touching the mouse
- **Handles large directories** — custom scrolling viewport keeps performance smooth regardless of entry count
- **Cross-platform** — native builds for Linux, macOS, and Windows

## Build from Source

**Requirements:** GCC 9+ / Clang 10+ / MSVC with C++17, plus `meson` and `ninja`.
 
```sh
meson setup build --buildtype=release
meson compile -C build
./build/fmpp
```
 
## How It Works
 
FileManager++ is built on [FTXUI](https://github.com/ArthurSonzogni/FTXUI) for terminal rendering. The layout is split into decoupled operational layers — each panel manages its own state independently.
 
## Credits
 
- [FTXUI](https://github.com/ArthurSonzogni/FTXUI) — terminal UI framework
- [Meson](https://mesonbuild.com/) — build system
