#include "ncf/Decorators.hpp"
#include "ncf/TextView.hpp"
#include "ncf/Application.hpp"
#include "ncf/Row.hpp"
#include "ncf/Column.hpp"

#include "Feedly.hpp"

#include "CategoryMenu.hpp"
#include "EntriesMenu.hpp"

#include <string>
#include <iostream>
#include <map>
#include <algorithm>

using namespace std;
using namespace ncf;

int main(int argc, char *argv[])
{
    Feedly::User user{
        "0f558b72-8e00-48b4-9f4a-7f97d8621968",
        "AxjaorhxtZDMv15jMMCr57KzxGf4-A1YLIxGwaGdlSQMU1xKqhBJfjEK2e9f-uWT_dwpOdPkKfECU6zjOBW-ZwnIiWe8YnaWB-jUmYahTYNnU-Cl_VXh2zRBfQsm6JpAT6NM_TCBHMc73pKTtifnVNrtWZ3A9McgePJ4mWgUeXBuPeEZYKE-nEF3SY_pyEOi04miSdXtOKUaJVChGaO8gKCfAe_4wA:feedlydev"
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

    vector<Menu::Item*> ctgItems;
    vector<Menu::Item*> entryItems;
        map<string, string> ctgs = server.Categories();
        for (auto& ctg : ctgs) {
            ctgItems.push_back(new Menu::Item(ctg.first, ctg.second));
        }

        vector<Feedly::Entry> entries = server.Entries("All");
        for (auto& entry : entries) {
            entryItems.push_back(new EntryItem(entry));
        }

    ctgMenu.setItems(ctgItems);
    entriesMenu.setItems(entryItems);

    top.add(new ncf::Border(&entriesMenu));
    top.add(new ncf::Border(&ctgMenu));

    body.add(&top, 0);
    body.add(new ncf::Border(&prev), 1);

    prev.setContent("Hello, World!");

    app.setInitialContext(&ctgMenu);

    body.draw();

    app.start();

    return 0;
}
