#include "api/Feedly.hpp"
#include "ncurses/Decorators.hpp"
#include "ncurses/TextView.hpp"
#include "ncurses/Application.hpp"
#include "app/CategoryMenu.hpp"
#include "app/EntriesMenu.hpp"
#include "ncurses/Layouts.hpp"
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
        "AwrS_rOER9mV3pd9CnGBH5Jckc96fv_yAfhaTWJdKWaXC9fuvGbDh4MW25kEvAiJi90p7yR41gSO8D02D20QLWm9hVF1utpbmcZlxwUgjxTIT-JgxjiIxkhmXnEPqW85VwUqNQO1hMtkAzc96bz8TR9ZulKg5Ci3PhyO7iECLFRZVo0Woz3aQwgq1cMaRKaHLkcTWECnIjbkTHm3pFreEBmoAu7zY_E:feedlydev"
    };

    Feedly server {
        user
    };

    ColumnLayout body        {};
    RowLayout    top         {};

    TextView     prev        {};
    EntriesMenu  entriesMenu {&prev};
    CategoryMenu ctgMenu     {&server, &entriesMenu};

    ctgMenu.OptionsOff(O_SHOWDESC);
    entriesMenu.OptionsOff(O_SHOWDESC);

    prev.CanFocus = false;

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

    ctgMenu.SetItems(ctgItems);
    entriesMenu.SetItems(entryItems);

    top.Add(new Border(&entriesMenu));
    top.Add(new Border(&ctgMenu));

    body.Add(new Border(&prev));
    body.Add(&top);

    prev.SetContent("Hello, World!");

    body.Show();

    app.SetInitialContext(&ctgMenu);

    app.Start();

    return 0;
}
