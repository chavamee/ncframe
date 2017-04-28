add_executable(single_menu menu/single_menu.cpp)
include_directories(${PROJECT_SOURCE_DIR}/ncf/inc)
target_link_libraries(single_menu ncf ncurses panel menu)
