#include "ncf/Application.hpp"
#include <algorithm>
#include <menu.h>
#include <panel.h>

using namespace std;

namespace ncf {

Application* Application::m_instance = nullptr;

Application* Application::getApplication()
{
    return m_instance;
}

Application::Application(bool enableColors) :
    m_hasColors(enableColors)
{
    using namespace ncurses;
    ::setlocale(LC_ALL, "");
    ncurses::initialize();

    ncurses::StdScr->enableKeypad(true);
    ncurses::StdScr->enableMeta(true);
    ::curs_set(0);

    if (::has_colors()) {
        ::start_color();

        ncurses::StdScr->setColor(1);
        ncurses::StdScr->setPalette({COLOR_YELLOW, COLOR_BLUE});
        ncurses::StdScr->setColor(2);
        ncurses::StdScr->setPalette({COLOR_CYAN,   COLOR_BLUE});
        ncurses::StdScr->setColor(3);
        ncurses::StdScr->setPalette({COLOR_BLACK,  COLOR_BLUE});
        ncurses::StdScr->setColor(4);
        ncurses::StdScr->setPalette({COLOR_BLACK,  COLOR_CYAN});
        ncurses::StdScr->setColor(5);
        ncurses::StdScr->setPalette({COLOR_BLUE,   COLOR_YELLOW});
        ncurses::StdScr->setColor(6);
        ncurses::StdScr->setPalette({COLOR_BLACK,  COLOR_GREEN});
    }

    m_instance = this;
}

//TODO: Refactor construction
Application::Application(Arguments args, bool enableColors) :
    Application(enableColors)
{
    m_hasColors = enableColors;
    //TODO:Parse command line options
    (void)args;
}

Application::~Application()
{
    ::endwin();
}

void Application::start()
{
    int ch;

    ::update_panels();
    ::doupdate();

    vector<Widget*>& widgetList = Widget::WidgetList;
    if (not m_currWdgtWithFocus) {
        m_currWdgtWithFocus = widgetList.front();
    }

    auto it = find(widgetList.begin(), widgetList.end(), m_currWdgtWithFocus);

    while ((ch = getch()) != m_killKey) {
        bool additionalEvent = false;
        bool fwd = true;

        do {
            if (ch == KEY_BTAB) {
                fwd = false;
                it = prev(it);
                additionalEvent = true;
            }  else if (ch == '\t') {
                fwd = true;
                it = next(it);
                additionalEvent = true;
            }

            if (it == widgetList.end()) {
                it = fwd ? widgetList.begin() : prev(it);
            }

            m_currWdgtWithFocus = *it;
        } while (not m_currWdgtWithFocus->canFocus);

        if (additionalEvent) {
            m_currWdgtWithFocus->onEvent(ch);
        } else {
            m_currWdgtWithFocus->onKeyEvent(ch);
        }

        ::refresh();
        ::update_panels();
        ::doupdate();
    }
}

}
