#include "ncf/ncurses/Menu.hpp"

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

Menu::MenuItem::MenuItem()
{
}

Menu::MenuItem::MenuItem(
        const std::string& name,
        const std::string& description
        ) :
    m_name(name),
    m_description(description)
{
    m_item = new_item(m_name.c_str(), m_description.c_str());
    if (m_item == NULL) {
        onError(E_SYSTEM_ERROR);
    }
}

Menu::MenuItem::MenuItem(const MenuItem& item) :
    m_name(item.m_name),
    m_description(item.m_description)
{
    m_item = new_item(m_name.c_str(), m_description.c_str());
    if (m_item == NULL) {
        throw std::runtime_error("menu item failed");
    }
}

Menu::MenuItem::~MenuItem()
{
    free_item(m_item);
}

Menu::MenuItem& Menu::MenuItem::operator=(const Menu::MenuItem& other)
{
    if (this != &other) {
        m_name = other.m_name;
        m_description = other.m_description;
        m_item = new_item(m_name.c_str(), m_description.c_str());
        if (m_item == NULL) {
            throw NCMenuException("Menu item failed: ", E_SYSTEM_ERROR);
        }
    }
    return *this;
}


Menu::Menu() :
    m_menu(nullptr),
    m_itemMark(nullptr),
    m_items(),
    m_window(),
    m_subWindow()
{
    m_menu = new_menu(nullptr);
    if (m_menu == nullptr) {
        onError(E_SYSTEM_ERROR);
    }
}

Menu::Menu(vector<MenuItem*>& items) :
    m_menu(nullptr),
    m_itemMark(nullptr),
    m_items(items),
    m_window(),
    m_subWindow()
{
    m_menu = new_menu(nullptr);
    if (m_menu == nullptr) {
        onError(E_SYSTEM_ERROR);
    }
    setItems(items);
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

    if (m_items.empty()) {
        set_menu_items(m_menu, nullptr);
    } else {
        set_menu_items(m_menu, _unpackItems(m_items));
    }

    if (m_isDrawn) {
        ITEM** oldItems = menu_items(m_menu);

        if (m_isPosted) {
            unpost();
        }
        if (!m_isPosted) {
            post();
        }

        delete[] oldItems;
    }
}

void Menu::setWindow(Window& win)
{
    onError( ::set_menu_win(m_menu, win.getHandle()) );
}

void Menu::setSubWindow(Window& win)
{
    onError( ::set_menu_sub(m_menu, win.getHandle()) );
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

ITEM** Menu::_unpackItems(vector<MenuItem*>& items)
{
    ITEM** rawItems = new ITEM*[items.size()+1];

    unsigned int i = 0;
    for (auto& item : items) {
        assert(item->m_item != nullptr);
        rawItems[i] = item->m_item;
        i++;
    }
    // make sure the last item is nullptr
    rawItems[i] = (ITEM*)nullptr;

    return rawItems;
}

// Set the current item
void Menu::setCurrentItem(MenuItem& item) {
    onError (::set_current_item(m_menu, item.m_item));
}

}
}
