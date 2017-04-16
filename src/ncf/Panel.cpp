#include "ncf/Panel.hpp"
#include "ncf/NCPanelException.hpp"

namespace ncf {

Panel::Panel() :
    Window(::stdscr)
{
    m_panel = ::new_panel(m_window);
    if (not m_panel) {
        throw NCPanelException("Failed to create panel");
    }
}

Panel::Panel(int height,
             int width,
             int y,
             int x) :
    Window(height, width, y, x)
{
    m_panel = ::new_panel(m_window);
    if (not m_panel) {
        throw NCPanelException("Failed to create panel");
    }
}

Panel::~Panel()
{
}

void Panel::top()
{
    ::top_panel(m_panel);
}

void Panel::hide()
{
    ::hide_panel(m_panel);
}

void Panel::show()
{
    ::show_panel(m_panel);
}

void Panel::move(const Point& pos)
{
    _onError( ::move_panel(m_panel, pos.x, pos.y) );
}

void Panel::refresh()
{
    ::update_panels();
    _onError( ::doupdate() );
}

void Panel::noutrefresh()
{
    ::update_panels();
}

void Panel::redrawAll()
{
    PANEL *pan;

    pan = ::panel_above(NULL);
    while (pan) {
        ::touchwin(panel_window(pan));
        pan = ::panel_above(pan);
    }
    ::update_panels();
    ::doupdate();
}

void Panel::_onError(int err)
{
    if (err != E_OK) {
        throw NCPanelException("Panel error", err);
    }
}

}
