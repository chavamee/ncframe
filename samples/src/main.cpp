#include "api/Feedly.hpp"

#include "ncf/Decorators.hpp"
#include "ncf/TextView.hpp"
#include "ncf/Application.hpp"
#include "ncf/Row.hpp"
#include "ncf/Column.hpp"

#include "app/CategoryMenu.hpp"
#include "app/EntriesMenu.hpp"

#include <string>
#include <iostream>
#include <map>
#include <algorithm>

using namespace std;
using namespace ncf;
using namespace ncf::ncurses;

int main(int argc, char *argv[])
{
    Feedly::User user{
        "9c68ac32-267d-4e67-9362-3d074bc11c34",
        "AzwoKrfxyb_kDf_-HmNittc3_EoKVXw8FL5_OX9c4Okhtmoj-Ep9h2-aZ1CSvlqU1xRbfA31giJGi1oYCm1if4PZmji-qE3wJqKpZp7l-bT7NiLvYHRlm83U_MFThMaBiLWFSLIagum2n3G2EAhG7_JcrlFjrli-kaqJ6w4RkYVl60C9Sjf5NYnaZIfm28ltcAzeUNU3h5EB2Q7CXDxxDIq6xo5ZAe-T:feedlydev"
    };

    Feedly server {
        user
    };

    //Application app {argc, argv};
    Application app {};

    Column body        {};
    Row    top         {};

    TextView     prev        {};
    EntriesMenu  entriesMenu {&prev};
    CategoryMenu ctgMenu     {&server, &entriesMenu};

    ctgMenu.optionsOff(O_SHOWDESC);
    entriesMenu.optionsOff(O_SHOWDESC);

    prev.canFocus = false;

    vector<ncurses::Menu::MenuItem*> ctgItems;
    vector<ncurses::Menu::MenuItem*> entryItems;
    /*try {
        map<string, string> ctgs = server.Categories();
        for (auto& ctg : ctgs) {
            ctgItems.push_back(new ncurses::Menu::MenuItem(ctg.first, ctg.second));
        }

        vector<Feedly::Entry> entries = server.Entries("All");
        for (auto& entry : entries) {
            entryItems.push_back(new EntryItem(entry));
        }
    } catch (std::exception& e) {
    }*/

    ctgItems.push_back(new ncurses::Menu::MenuItem("Test", "Test"));
    Feedly::Entry entry {"Test", "Test", "Test", "Test", "Test"};
    entryItems.push_back(new EntryItem(entry));
    ctgMenu.setItems(ctgItems);
    entriesMenu.setItems(entryItems);

    top.add(new Border(&entriesMenu));
    top.add(new Border(&ctgMenu));

    body.add(&top, 0);
    body.add(new Border(&prev), 1);

    prev.setContent("Hello, World!");

    app.setInitialContext(&ctgMenu);

    body.draw();

    app.start();

    return 0;
}
