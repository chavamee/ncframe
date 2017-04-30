include_directories(
    ${NCF_INCLUDE_DIRS})
add_library(${NCF_LIBRARIES} SHARED
    Application.cpp
    Column.cpp
    Menu.cpp
    Row.cpp
    Widget.cpp
    Menu.cpp
    Panel.cpp
    Pad.cpp
    TextBox.cpp
    Window.cpp
    )

target_link_libraries(${NCF_LIBRARIES}
    ncurses menu panel
    )
