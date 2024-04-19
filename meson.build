project('ffui',
  'cpp',
  default_options: ['warning_level=3', 'cpp_std=c++17'],
  license: 'MIT',
  meson_version: '>=1.3.0',
  version: '1.0',
)

curses_dep = dependency('curses')
rapidfuzz_dep = dependency('rapidfuzz')
deps = [curses_dep, rapidfuzz_dep]

app_sources = ['src/main.cpp', 'src/ffui.cpp']
executable('ffui_app', app_sources, dependencies: deps)

lib_sources = ['src/ffui.cpp']
library('ffui', lib_sources, dependencies: deps)
