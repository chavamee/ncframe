#include "ncf/ncurses/Panel.hpp"
#include "ncf/Menu.hpp"
#include "ncf/Application.hpp"

using namespace std;

namespace ncf {

Menu::Menu() :
    m_menu(make_unique<ncurses::Menu>())
{
}

void Menu::onMouseEvent(int ch)
{
    (void)ch;
}

int Menu::onKeyEvent(int ch)
{
    switch(ch) {
        case KEY_DOWN      : return m_menu->drive(REQ_DOWN_ITEM);
        case CTRL('N')     : return m_menu->drive(REQ_NEXT_ITEM);
        case KEY_UP        : return m_menu->drive(REQ_UP_ITEM);
        case CTRL('P')     : return m_menu->drive(REQ_PREV_ITEM);

        case CTRL('T')     : return m_menu->drive(REQ_TOGGLE_ITEM);

        /*
         * Depending on the terminal, the Enter/Send key will return one of
         * the following:
         */
        case '\r'          :
        case '\n'          :
        case KEY_ENTER     : _invokeAction(m_menu->currentItem()); return 1;

        case KEY_HOME      : return m_menu->drive(REQ_FIRST_ITEM);
        case KEY_LEFT      : return m_menu->drive(REQ_LEFT_ITEM);
        case KEY_RIGHT     : return m_menu->drive(REQ_RIGHT_ITEM);
        case KEY_END       : return m_menu->drive(REQ_LAST_ITEM);
    }
    return 0;
}

bool Menu::onEvent(int ch)
{
    (void)ch;
    return false;
}


void Menu::draw(unique_ptr<ncurses::Window> window, unique_ptr<ncurses::Window> subWindow)
{
    if (window.get() != nullptr) {

        window->enableKeypad(true);
        window->enableMeta(true);

        //TODO: initializeItems()

        m_menu->setWindow(*window);

        subWindow = make_unique<ncurses::Window>(
                *window,
                window->height()-2, window->width()-2, 1, 1,
                false
                );

        m_menu->setSubWindow(*subWindow);

        //TODO: These should be treated as defaults. Maybe do at construction
        // to ensure that after construction if the user needs to change the
        // format this will not conflict.
        m_menu->setFormat({.height = window->height() - 2, .width = 1});
        m_menu->setMark("*");

        subWindow->enableKeypad(true);
        subWindow->enableMeta(true);

        Application* app = Application::getApplication();
        if (app) {
            m_menu->setForeground(app->foregrounds());
            m_menu->setBackground(app->backgrounds());
            m_menu->setGrey(app->inactives());
        }

        m_menu->post();
        window->refresh();

        setWindow(std::move(window));
        setSubWindow(std::move(subWindow));
    } else {
        //TODO: Define defaults
    }

    m_isDrawn = true;
}

bool Menu::_invokeAction(ncurses::Menu::MenuItem& item)
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

}
