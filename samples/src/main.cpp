#include "api/Feedly.hpp"

#include "ncf/Decorators.hpp"
#include "ncf/TextView.hpp"
#include "ncf/Application.hpp"
#include "ncf/Layouts.hpp"

#include "app/CategoryMenu.hpp"
#include "app/EntriesMenu.hpp"

#include <string>
#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[])
{
    Application app(argc, argv);

    Feedly::User user{
        "0f558b72-8e00-48b4-9f4a-7f97d8621968",
        "Az8RkrRAn5dR0MpoZUmSaYr55MsrclittquxiHIPiHgOU1hpkzCiH881WYeIMqKzo3fy5ZKzqjgMCjml9OYxTwkRXjAmycKeXoBh4ddQVwAr6Efb5kJy4_iR1q8-0OkOw2ZXiZC1m_x88lmUwp04ByckJq2ErTL0G8AhTlNfmWtvbVjF7Cqju3_x_WJTnsbCzPRSR6zg5kxLhVgzoIxgEtlgSQNmFw:feedlydev"
    };

    Feedly server {
        user
    };

    ColumnLayout body        {};
    RowLayout    top         {};

    TextView     prev        {};
    EntriesMenu  entriesMenu {&prev};
    CategoryMenu ctgMenu     {&server, &entriesMenu};

    ctgMenu.optionsOff(O_SHOWDESC);
    entriesMenu.optionsOff(O_SHOWDESC);

    prev.canFocus = false;

    vector<MenuItem*> ctgItems;
    map<string, string> ctgs = server.Categories();
    for (auto& ctg : ctgs) {
        ctgItems.push_back(new MenuItem(ctg.first, ctg.second));
    }

    vector<MenuItem*> entryItems;
    vector<Feedly::Entry> entries = server.Entries("All");
    for (auto& entry : entries) {
        entryItems.push_back(new EntryItem(entry));
    }

    ctgMenu.setItems(ctgItems);
    entriesMenu.setItems(entryItems);

    top.add(new Border(&entriesMenu));
    top.add(new Border(&ctgMenu));

    body.add(new Border(&prev));
    body.add(&top);

    prev.setContent("Hello, World!");

    body.show();

    app.setInitialContext(&ctgMenu);

    app.start();

    return 0;
}
