#include "ncf/Menu.hpp"
#include "ncf/Application.hpp"

#include <menu.h>
#include <cassert>
#include <stdexcept>

//TODO: Keep flag for already drawn check?
//TODO: Do not create ncurses handle for
//      Menu Items until just before it is
//      added to a menu

using namespace std;

Menu::Menu() :
    m_handle(NULL),
    m_itemMark(nullptr),
    m_items()
{
}

Menu::Menu(const Rect& rect) :
    Widget {rect},
    m_handle(NULL),
    m_itemMark(nullptr),
    m_items()
{
}

Menu::Menu(const Rect& rect, vector<MenuItem*>& items) :
    Widget {rect},
    m_handle(NULL),
    m_itemMark(nullptr),
    m_items(items)
{
}

Menu::~Menu()
{
    // Free all items before freeing the menu
    if (m_handle) {
        ::free_menu(m_handle);
        m_items.clear();
        m_handle = NULL;
    }

}


//TODO
// initializeItems()
// {
// for (auto& item : m_items)
//  item.m_handle = new_item(...)
//}

void Menu::draw(unique_ptr<Window> window, unique_ptr<Window> subWindow)
{
    if (window.get() != nullptr) {

        keypad(window->getHandle(), true);
        meta(window->getHandle(), true);

        //TODO: initializeItems()

        m_handle = new_menu(_unpackItems(m_items));
        if (m_handle == NULL) {
            onError(E_SYSTEM_ERROR);
        }

        set_menu_win(m_handle, window->getHandle());

        subWindow = make_unique<Window>(
                *window,
                window->height()-2, window->width()-2, 1, 1,
                false
                );

        set_menu_sub(m_handle, subWindow->getHandle());

        //TODO: These should be treated as defaults. Maybe do at construction
        // to ensure that after construction if the user needs to change the
        // format this will not conflict.
        setFormat({.height = window->height() - 2, .width = 1});
        setMark(m_itemMark ? m_itemMark : "*");

        Application* app = Application::getApplication();
        if (app) {
            ::set_menu_fore(m_handle, app->foregrounds());
            ::set_menu_back(m_handle, app->backgrounds());
            ::set_menu_grey(m_handle, app->inactives());
        }

        post();
        window->refresh();

        setWindow(std::move(window));
        setSubWindow(std::move(subWindow));
    } else {
        //TODO: Define defaults
    }

    m_isDrawn = true;
}

void Menu::setItems(vector<MenuItem*>& items)
{
    //TODO: Implement with a swap or clone function
    m_items = items;
    for (auto& item : m_items) {
        item->m_menu = this;
    }

    if (m_isDrawn) {
        ITEM** oldItems = menu_items(m_handle);

        if (m_isPosted) {
            unpost();
        }
        if (m_items.empty()) {
            set_menu_items(m_handle, NULL);
        } else {
            set_menu_items(m_handle, _unpackItems(m_items));
        }
        if (!m_isPosted) {
            post();
        }

        delete[] oldItems;
    }
}

void Menu::onMouseEvent(int ch)
{
    (void)ch;
}

int Menu::onKeyEvent(int ch)
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
        case KEY_ENTER     : _invokeAction(currentItem()); return 1;

        case KEY_HOME      : return ::menu_driver(m_handle, REQ_FIRST_ITEM);
        case KEY_LEFT      : return ::menu_driver(m_handle, REQ_LEFT_ITEM);
        case KEY_RIGHT     : return ::menu_driver(m_handle, REQ_RIGHT_ITEM);
        case KEY_END       : return ::menu_driver(m_handle, REQ_LAST_ITEM);
    }
    return 0;
}

bool Menu::onEvent(int ch)
{
    (void)ch;
    return false;
}

bool Menu::_invokeAction(MenuItem& item)
{
    if (static_cast<int>(item.options()) & O_SELECTABLE)
    {
        item.action();
        onItemAction(&item);
        refresh();
    } else {
        //On_Not_Selectable(c);
    }

    return true;
}

ITEM** Menu::_unpackItems(vector<MenuItem*>& items)
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

void Menu::setDefaultAttributes()
{
    Application* app = Application::getApplication();
    if (app) {
        ::set_menu_fore(m_handle, app->foregrounds());
        ::set_menu_back(m_handle, app->backgrounds());
        ::set_menu_grey(m_handle, app->inactives());
    }
}

// Set the current item
void Menu::setCurrentItem(MenuItem& item) {
    onError (::set_current_item(m_handle, item.m_handle));
}
