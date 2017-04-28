#include <ncf/Panel.hpp>
#include <ncf/Menu.hpp>
#include <ncf/Application.hpp>

#include <menu.h>
#include <cassert>
#include <stdexcept>

//TODO: Keep flag for already drawn check?
//TODO: Do not create ncurses handle for
//      Menu Items until just before it is
//      added to a menu

using namespace std;

namespace ncf {

Menu::Item::Item()
{
}

Menu::Item::Item(
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

Menu::Item::Item(const Item& item) :
    m_name(item.m_name),
    m_description(item.m_description)
{
    m_item = new_item(m_name.c_str(), m_description.c_str());
    if (m_item == NULL) {
        throw std::runtime_error("menu item failed");
    }
}

Menu::Item::~Item()
{
    free_item(m_item);
}

Menu::Item& Menu::Item::operator=(const Menu::Item& other)
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

Menu::Menu(vector<Item*>& items) :
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

void Menu::onMouseEvent(int ch)
{
    (void)ch;
}

int Menu::onKeyEvent(int ch)
{
    switch(ch) {
        case KEY_DOWN      : return drive(REQ_DOWN_ITEM);
        case CTRL('N')     : return drive(REQ_NEXT_ITEM);
        case KEY_UP        : return drive(REQ_UP_ITEM);
        case CTRL('P')     : return drive(REQ_PREV_ITEM);

        case CTRL('T')     : return drive(REQ_TOGGLE_ITEM);

        /*
         * Depending on the terminal, the Enter/Send key will return one of
         * the following:
         */
        case '\r'          :
        case '\n'          :
        case KEY_ENTER     : _invokeAction(currentItem()); return 1;

        case KEY_HOME      : return drive(REQ_FIRST_ITEM);
        case KEY_LEFT      : return drive(REQ_LEFT_ITEM);
        case KEY_RIGHT     : return drive(REQ_RIGHT_ITEM);
        case KEY_END       : return drive(REQ_LAST_ITEM);
    }
    return 0;
}

bool Menu::onEvent(int ch)
{
    (void)ch;
    return false;
}

void Menu::draw(unique_ptr<Window> window, unique_ptr<Window> subWindow)
{
    if (window.get() != nullptr) {

        window->enableKeypad(true);
        window->enableMeta(true);

        //TODO: initializeItems()

        Menu::setWindow(*window);

        subWindow = make_unique<Panel>(
                *window,
                window->height()-2, window->width()-2, 1, 1,
                false
                );

        Menu::setSubWindow(*subWindow);

        //TODO: These should be treated as defaults. Maybe do at construction
        // to ensure that after construction if the user needs to change the
        // format this will not conflict.
        setFormat({.height = window->height() - 2, .width = 1});
        setMark("*");

        subWindow->enableKeypad(true);
        subWindow->enableMeta(true);

        Application* app = Application::getApplication();
        if (app) {
            setForeground(app->foregrounds());
            setBackground(app->backgrounds());
            setGrey(app->inactives());
        }

        post();
        window->refresh();
        subWindow->refresh();

        Widget::setWindow(std::move(window));
        Widget::setSubWindow(std::move(subWindow));
    } else {
        //TODO: Define defaults
    }

    m_isDrawn = true;
}

bool Menu::_invokeAction(Menu::Item& item)
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

//TODO
// initializeItems()
// {
// for (auto& item : m_items)
//  item.m_menu = new_item(...)
//}

void Menu::setItems(vector<Item*>& items)
{
    //TODO: Implement with a swap or clone function
    m_items = items;
    for (auto& item : m_items) {
        item->m_menu = this;
    }

    ITEM** oldItems = nullptr;
    if (m_isDrawn) {
        unpost();
         oldItems = menu_items(m_menu);
    }

    if (m_items.empty()) {
        set_menu_items(m_menu, nullptr);
    } else {
        set_menu_items(m_menu, _unpackItems(m_items));
    }

    if (m_isDrawn) {
        post();
        if (oldItems != nullptr) {
            delete[] oldItems;
        }
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

ITEM** Menu::_unpackItems(vector<Item*>& items)
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
void Menu::setCurrentItem(Item& item) {
    onError (::set_current_item(m_menu, item.m_item));
}

} // namespace ncf
