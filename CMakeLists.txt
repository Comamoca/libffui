cmake_minimum_required(VERSION 3.5)

set(OUT_NAME app)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(
  ffui
  VERSION 1.0
  LANGUAGES CXX)


include(FetchContent)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

FetchContent_Declare(rapidfuzz
  GIT_REPOSITORY https://github.com/rapidfuzz/rapidfuzz-cpp.git
  GIT_TAG main)
FetchContent_MakeAvailable(rapidfuzz)

add_executable(app src/main.cpp src/ffui.cpp)

# add_executable(appc src/main.c src/ffui.cpp)

target_link_libraries(app PRIVATE rapidfuzz::rapidfuzz)
target_link_libraries(app PRIVATE ${CURSES_LIBRARY})

# target_link_libraries(appc PRIVATE rapidfuzz::rapidfuzz)
# target_link_libraries(appc PRIVATE ${CURSES_LIBRARY})

add_library(ffui STATIC
    src/ffui.cpp
)

target_link_libraries(ffui PRIVATE rapidfuzz::rapidfuzz)
target_link_libraries(ffui PRIVATE ${CURSES_LIBRARY})
