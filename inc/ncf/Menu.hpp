#ifndef NCF_WIDGETS_MENU_H
#define NCF_WIDGETS_MENU_H

#include "ncf/Widget.hpp"
#include "ncf/ncurses/Menu.hpp"

namespace ncf {

class Menu : public Widget {

public:
    Menu();

    void onMouseEvent (int ch) override;

    int onKeyEvent(int ch) override;

    bool onEvent(int ch) override;

    void draw(std::unique_ptr<ncurses::Window> window = {}, std::unique_ptr<ncurses::Window> subWindow = {}) override;
    void optionsOff(Menu_Options opts)
    {
        m_menu->optionsOff(opts);
    }

    void optionsOn(Menu_Options opts)
    {
        m_menu->optionsOff(opts);
    }

    ncurses::Menu::MenuItem& currentItem()
    {
        return m_menu->currentItem();
    }

    void setItems(std::vector<ncurses::Menu::MenuItem*>& items)
    {
        m_menu->setItems(items);
    }

    virtual void onItemAction(ncurses::Menu::MenuItem* item)
    {
        NCF_UNUSED(item);
    }

private:
    bool m_isDrawn = false;

    std::unique_ptr<ncurses::Menu> m_menu;

    bool _invokeAction(ncurses::Menu::MenuItem& item);

};

}

#endif
