project(ncframe)
set (srcs Application.cpp Column.cpp Menu.cpp Row.cpp TextView.cpp View.cpp Widget.cpp Menu.cpp Panel.cpp Pad.cpp Window.cpp)
add_library(ncf SHARED ${srcs})
