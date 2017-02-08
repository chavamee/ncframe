#include "ncf/Application.hpp"
#include <algorithm>
#include <menu.h>
#include <panel.h>

using namespace std;

Application* Application::m_instance = nullptr;

Application* Application::getApplication()
{
    return m_instance;
}

Application::Application(bool enableColors) :
    m_hasColors(enableColors)
{
    ::setlocale(LC_ALL, "");
    ::initscr();

    ::cbreak();
    ::noecho();
    ::keypad(stdscr, true);
    ::meta(stdscr, true);
    ::curs_set(0);

    m_rootWindow = new Window(::stdscr);

    if (::has_colors()) {
        ::start_color();

        m_rootWindow->setColor(1);
        m_rootWindow->setPalette({COLOR_YELLOW, COLOR_BLUE});
        m_rootWindow->setColor(2);
        m_rootWindow->setPalette({COLOR_CYAN,   COLOR_BLUE});
        m_rootWindow->setColor(3);
        m_rootWindow->setPalette({COLOR_BLACK,  COLOR_BLUE});
        m_rootWindow->setColor(4);
        m_rootWindow->setPalette({COLOR_BLACK,  COLOR_CYAN});
        m_rootWindow->setColor(5);
        m_rootWindow->setPalette({COLOR_BLUE,   COLOR_YELLOW});
        m_rootWindow->setColor(6);
        m_rootWindow->setPalette({COLOR_BLACK,  COLOR_GREEN});
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
    delete m_rootWindow;
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
