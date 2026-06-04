project(
    'FileManagerPlusPlus',
    'cpp',
    version: '0.1',
    default_options: ['cpp_std=c++17'],
)

ftxui_screen_dep = dependency('ftxui-screen')
ftxui_dom_dep = dependency('ftxui-dom')
ftxui_comp_dep = dependency('ftxui-component')

sources = files(
    'src/file_system.cpp',
    'src/main.cpp',
    'src/ui/components.cpp',
)

executable(
    'fmpp',
    sources,
    dependencies: [ftxui_screen_dep, ftxui_dom_dep, ftxui_comp_dep],
    include_directories: include_directories('src'),
)
