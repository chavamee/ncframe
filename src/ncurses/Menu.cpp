#include "ncurses/Menu.hpp"
#include "ncurses/NCException.hpp"

#include <menu.h>
#include <cassert>
#include <stdexcept>

//TODO: Keep flag for already drawn check?
//TODO: Do not create ncurses handle for
//      Menu Items until just before it is
//      added to a menu

using namespace std;

MenuItem::MenuItem()
{
}

MenuItem::MenuItem(
        std::string name,
        std::string description
        ) :
    m_name(name),
    m_description(description)
{
    m_handle = new_item(m_name.c_str(), m_description.c_str());
    if (m_handle == NULL) {
        throw std::runtime_error("menu item failed");
    }
}

MenuItem::MenuItem(const MenuItem& item) :
    m_name(item.m_name),
    m_description(item.m_description)
{
    m_handle = new_item(m_name.c_str(), m_description.c_str());
    if (m_handle == NULL) {
        throw std::runtime_error("menu item failed");
    }
}

MenuItem::~MenuItem()
{
    free_item(m_handle);
}

MenuItem& MenuItem::operator=(const MenuItem& other)
{
    if (this != &other) {
        m_name = other.m_name;
        m_description = other.m_description;
        m_handle = new_item(m_name.c_str(), m_description.c_str());
        if (m_handle == NULL) {
            throw std::runtime_error("menu item failed");
        }
    }
    return *this;
}

Menu_Options MenuItem::options() {
    return ::item_opts(m_handle);
}

void MenuItem::set_options (Menu_Options opts) {
    set_item_opts (m_handle, opts);
}


Menu::Menu() :
    m_handle(NULL),
    m_itemMark(nullptr),
    m_subWindow{},
    m_items()
{
}

Menu::Menu(int height, int width, int y, int x) :
    m_handle(NULL),
    m_itemMark(nullptr),
    m_mainWindow {new Window {height, width, y, x}},
    m_subWindow{},
    m_items()
{
}

Menu::Menu(int height, int width, int y, int x, vector<MenuItem*>& items) :
    m_handle(NULL),
    m_itemMark(nullptr),
    m_mainWindow {new Window {height, width, y, x}},
    m_subWindow {},
    m_items(items)
{
}

Menu::~Menu()
{
    // Free all items before freeing the menu
    m_items.clear();

    ITEM** items = menu_items(m_handle);
    free_menu(m_handle);
    m_handle = NULL;
    delete[] items;
}


//TODO
// initializeItems()
// {
// for (auto& item : m_items)
//  item.m_handle = new_item(...)
//}

void Menu::Draw(std::unique_ptr<Window> mainWindow)
{
    if (mainWindow.get() != nullptr) {
        m_mainWindow = std::move(mainWindow);
    } else {
        //TODO: Define defaults
    }

    keypad(m_mainWindow->GetHandle(), true);
    meta(m_mainWindow->GetHandle(), true);


    //TODO: initializeItems()

    m_handle = new_menu(unpackItems(m_items));
    if (m_handle == NULL) {
        throw std::runtime_error("menu error");
    }

    int subRows, subCols;
    scale_menu(m_handle, &subRows, &subCols);
    set_menu_win(m_handle, m_mainWindow->GetHandle());

    if (subRows < m_mainWindow->Height() - 2 && subCols < m_mainWindow->Width() - 2) {
        m_subWindow = make_unique<Window>(
                *m_mainWindow,
                subRows, subCols, 1, 1,
                false
                );
        set_menu_sub(m_handle, m_subWindow->GetHandle());
    } else {
        throw NCException("No room left for menu");
    }

    set_menu_mark(m_handle, m_itemMark ? m_itemMark : "*");

    post_menu(m_handle);
    m_isDrawn = true;
}

void Menu::SetItems(vector<MenuItem*>& items)
{
    //TODO: Implement with a swap or clone function
    m_items = items;
    for (auto& item : m_items) {
        item->m_menu = this;
    }

    if (m_isDrawn) {
        ITEM** oldItems = menu_items(m_handle);

        unpost_menu(m_handle);
        if (m_items.empty()) {
            set_menu_items(m_handle, NULL);
        } else {
            set_menu_items(m_handle, unpackItems(m_items));
        }
        post_menu(m_handle);

        delete[] oldItems;
    }
}

void Menu::OnMouseEvent(int ch)
{
    (void)ch;
}

int Menu::OnKeyEvent(int ch)
{
    switch(ch) {
        case KEY_DOWN      : return ::menu_driver(m_handle, REQ_DOWN_ITEM);
        case CTRL('N')     : return ::menu_driver(m_handle, REQ_NEXT_ITEM);
        case KEY_UP        : return ::menu_driver(m_handle, REQ_UP_ITEM);
        case CTRL('P')     : return ::menu_driver(m_handle, REQ_PREV_ITEM);

        case CTRL('T')     : return ::menu_driver(m_handle, REQ_TOGGLE_ITEM);

        /*
         * Depending on the terminal, the Enter/Send key will return one of
         * the following:
         */
        case '\r'          :
        case '\n'          :
        case KEY_ENTER     : invokeAction(CurrentItem()); return 1;

        case KEY_HOME      : return ::menu_driver(m_handle, REQ_FIRST_ITEM);
        case KEY_LEFT      : return ::menu_driver(m_handle, REQ_LEFT_ITEM);
        case KEY_RIGHT     : return ::menu_driver(m_handle, REQ_RIGHT_ITEM);
        case KEY_END       : return ::menu_driver(m_handle, REQ_LAST_ITEM);
    }
    return 0;
}

bool Menu::OnEvent(int ch)
{
    (void)ch;
    return false;
}

bool Menu::invokeAction(MenuItem& item)
{
    if (static_cast<int>(item.options()) & O_SELECTABLE)
    {
        item.Action();
        OnItemAction(&item);
        refresh();
    } else {
        //On_Not_Selectable(c);
    }

    return true;
}

ITEM** Menu::unpackItems(vector<MenuItem*>& items)
{
    ITEM** rawItems = new ITEM*[items.size()+1];

    unsigned int i = 0;
    for (auto& item : items) {
        assert(item->m_handle != NULL);
        rawItems[i] = item->m_handle;
        i++;
    }
    // make sure the last item is NULL
    rawItems[i] = (ITEM*)NULL;

    return rawItems;
}
