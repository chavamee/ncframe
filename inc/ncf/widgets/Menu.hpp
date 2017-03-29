#ifndef NCF_WIDGETS_MENU_H
#define NCF_WIDGETS_MENU_H

#include "ncf/ncurses/Menu.hpp"

namespace ncf {
namespace widgets {

class Menu : ncurses::Menu, Widget {

public:
    void onMouseEvent (int ch) override;

    int onKeyEvent(int ch) override;

    bool onEvent(int ch) override;

    void draw(std::unique_ptr<Window> window = {}, std::unique_ptr<Window> subWindow = {}) override;

private:
    int temp = 0;

};

}
}

#endif
