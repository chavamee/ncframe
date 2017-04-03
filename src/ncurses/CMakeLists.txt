project(ncframe_ncurses)
set(ncurses_srcs Menu.cpp Pad.cpp Panel.cpp Window.cpp)
add_library(ncf_ncurses SHARED ${ncurses_srcs})
