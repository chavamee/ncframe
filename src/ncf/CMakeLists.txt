project(ncframe)
set (srcs Application.cpp Column.cpp Menu.cpp Row.cpp TextView.cpp View.cpp Widget.cpp)
add_library(ncf SHARED ${srcs})
