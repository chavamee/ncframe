project(ncframe_ncurses)
set(ncurses_srcs Menu.cpp Pad.cpp Panel.cpp Window.cpp)
add_compile_options(-Wall -Wextra -Weffc++)
add_library(ncf_ncurses SHARED ${ncurses_srcs})

