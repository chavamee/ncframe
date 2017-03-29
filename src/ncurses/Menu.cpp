#include "ncf/ncurses/Menu.hpp"
#include "ncf/Application.hpp"

#include <menu.h>
#include <cassert>
#include <stdexcept>

//TODO: Keep flag for already drawn check?
//TODO: Do not create ncurses handle for
//      Menu Items until just before it is
//      added to a menu

using namespace std;

namespace ncf {
namespace ncurses {

Menu::Menu() :
    m_menu(nullptr),
    m_itemMark(nullptr),
    m_items()
{
}

Menu::Menu(const Rect& rect) :
    Widget {rect},
    m_menu(nullptr),
    m_itemMark(nullptr),
    m_items()
{
}

Menu::Menu(const Rect& rect, vector<MenuItem*>& items) :
    Widget {rect},
    m_menu(nullptr),
    m_itemMark(nullptr),
    m_items(items)
{
}

Menu::~Menu()
{
    // Free all items before freeing the menu
    if (m_menu) {
        m_items.clear();
        ::free_menu(m_menu);
        m_menu = nullptr;
    }

}


//TODO
// initializeItems()
// {
// for (auto& item : m_items)
//  item.m_menu = new_item(...)
//}

void Menu::setItems(vector<MenuItem*>& items)
{
    //TODO: Implement with a swap or clone function
    m_items = items;
    for (auto& item : m_items) {
        item->m_menu = this;
    }

    if (m_isDrawn) {
        ITEM** oldItems = menu_items(m_menu);

        if (m_isPosted) {
            unpost();
        }
        if (m_items.empty()) {
            set_menu_items(m_menu, nullptr);
        } else {
            set_menu_items(m_menu, _unpackItems(m_items));
        }
        if (!m_isPosted) {
            post();
        }

        delete[] oldItems;
    }
}

void Menu::setWindow(Window& win)
{
    _onError( set_menu_win(m_menu, win.getHandle()`) );
}

void Menu::setSubWindow(Window& win)
{
    _onError( set_menu_sub(m_menu, win.getHandle() );
}

void Menu::setWindow(unique_ptr<Window> win)
{
    m_window = std::move(win);
    setWindow(*m_window);
}

void Menu::setSubWindow(unique_ptr<Window> win)
{
    m_subWindow = std::move(win);
    setSubWindow(*m_subWindow);
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
        assert(item->m_menu != nullptr);
        rawItems[i] = item->m_menu;
        i++;
    }
    // make sure the last item is nullptr
    rawItems[i] = (ITEM*)nullptr;

    return rawItems;
}

void Menu::setDefaultAttributes()
{
    Application* app = Application::getApplication();
    if (app) {
        ::set_menu_fore(m_menu, app->foregrounds());
        ::set_menu_back(m_menu, app->backgrounds());
        ::set_menu_grey(m_menu, app->inactives());
    }
}

// Set the current item
void Menu::setCurrentItem(MenuItem& item) {
    onError (::set_current_item(m_menu, item.m_menu));
}

}
}
