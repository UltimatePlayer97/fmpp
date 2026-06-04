project(
    'fmpp',
    'cpp',
    version: '0.1.0',
    default_options: ['cpp_std=c++17', 'warning_level=3'],
)

ftxui_dep = dependency('ftxui-component')

subdir('src/ui/')

main_sources = files('src/file_system.cpp', 'src/main.cpp', 'src/ui/components.cpp')

all_sources = [main_sources, component_sources]

executable('fmpp', all_sources, dependencies: ftxui_dep, install: true)
