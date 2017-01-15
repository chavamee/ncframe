#include "ncurses/Application.hpp"
#include "ncurses/Widgets.hpp"
#include <algorithm>
#include <menu.h>
#include <panel.h>

using namespace std;

Application::Application()
{
    setlocale(LC_ALL, "");
    initscr();

    start_color();

    cbreak();
    noecho();
    keypad(stdscr, true);
    meta(stdscr, true);
    curs_set(0);
    m_rootWindow = new Window(::stdscr);

    m_rootWindow->SetColor(1);
    m_rootWindow->SetPalette(COLOR_YELLOW,COLOR_BLUE);
    m_rootWindow->SetColor(2);
    m_rootWindow->SetPalette(COLOR_CYAN,COLOR_BLUE);
    m_rootWindow->SetColor(3);
    m_rootWindow->SetPalette(COLOR_BLACK,COLOR_BLUE);
    m_rootWindow->SetColor(4);
    m_rootWindow->SetPalette(COLOR_BLACK,COLOR_CYAN);
    m_rootWindow->SetColor(5);
    m_rootWindow->SetPalette(COLOR_BLUE,COLOR_YELLOW);
    m_rootWindow->SetColor(6);
    m_rootWindow->SetPalette(COLOR_BLACK,COLOR_GREEN);
}

Application::Application(bool enableColors) :
    m_enableColors(enableColors)
{
}

Application::Application(int argc, char *argv[], bool enableColors) :
    Application()
{
    m_enableColors = enableColors;
    //TODO:Parse command line options
    (void)argc;
    (void)argv;
}

Application::~Application()
{
    delete m_rootWindow;
    endwin();
}

void Application::Start()
{
    int ch;

    update_panels();
    doupdate();

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
                it = next(it);
                additionalEvent = true;
            }

            if (it == widgetList.end()) {
                it = fwd ? widgetList.begin() : prev(it);
            }

            m_currWdgtWithFocus = *it;
        } while (not m_currWdgtWithFocus->CanFocus);

        if (additionalEvent) {
            m_currWdgtWithFocus->OnEvent(ch);
        } else {
            m_currWdgtWithFocus->OnKeyEvent(ch);
        }

        refresh();
        update_panels();
        doupdate();
    }
}
