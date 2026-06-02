cmake_minimum_required(VERSION 3.31)
project(FileManagerPlusPlus CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
    GIT_TAG v6.1.9
)

add_executable(fmpp)

target_sources(fmpp PRIVATE
    src/main.cpp
)
target_link_libraries(fmpp PRIVATE
  ftxui::screen
  ftxui::dom
  ftxui::component
)
target_include_directories(fmpp PRIVATE
    ${ftxui_SOURCE_DIR}/include
)

FetchContent_MakeAvailable(ftxui)
