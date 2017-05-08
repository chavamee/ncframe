#include <ncf/Application.hpp>
#include <ncf/Menu.hpp>

using namespace ncf;

int main(void)
{
    Application app;

    Menu menu {
        new Menu::Item {"Vim",    "A highly configurable text editor"},
        new Menu::Item {"Nano",   "The GNU Nano"},
        new Menu::Item {"Emacs",  "An extensible, customizable, free/libre text editor"},
        new Menu::Item {"Sublime","The text editor you'll fall in love with"},
        new Menu::Item {"Atom",   "A hackable editor for the 21st Century"},
        new Menu::Item {"Gedit",  "The GNOME text editor"}
    };

    menu.draw();

    app.start();

    return 0;
}
