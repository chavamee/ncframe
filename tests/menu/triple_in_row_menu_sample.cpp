#include <ncf/Application.hpp>
#include <ncf/Menu.hpp>
#include <ncf/Row.hpp>
#include <ncf/Decorators.hpp>

using namespace ncf;

int main(void)
{
    Application app;

    Menu firstMenu {
        new ncf::Menu::Item {"Vim",    "A highly configurable text editor"},
        new ncf::Menu::Item {"Nano",   "The GNU Nano"}
    };

    Menu secondMenu {
        new ncf::Menu::Item {"Atom",   "A hackable editor for the 21st Century"},
        new ncf::Menu::Item {"Gedit",  "The GNOME text editor"}
    };

    Menu thirdMenu {
        new ncf::Menu::Item {"Emacs",  "An extensible, customizable, free/libre text editor"},
        new ncf::Menu::Item {"Sublime","The text editor you'll fall in love with"}
    };


    Row row;

    row.add(new Border(&firstMenu));
    row.add(new Border(&secondMenu));
    row.add(new Border(&thirdMenu));

    row.draw();

    app.start();

    return 0;
}
