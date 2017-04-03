cmake_minimum_required(VERSION 2.6)
project(ncframe)

option(BUILD_FRAMEWORK "Build NCFramework. Turn off if you only need ncurses bindings" on)

include_directories("${PROJECT_SOURCE_DIR}/inc")
add_subdirectory(src/ncurses)

add_subdirectory(src/ncf)
add_subdirectory(samples)
