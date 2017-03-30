#include "ncf/ncurses/Panel.hpp"
#include "ncf/ncurses/NCPanelException.hpp"

namespace ncf {
namespace ncurses {

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

Panel& Panel::operator=(const Panel& rhs)
{
    if (this != &rhs) {
        *this = rhs;
        Panel::operator=(rhs);
    }

    return *this;
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

void Panel::move(const Point& point)
{
    _onError( ::move_panel(m_panel, point.x, point.y) );
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

void Panel::frame(const std::string& title,const std::string& btitle)
{
    box();
    if (not title.empty() && not btitle.empty()) {
        label(title, btitle);
    }
}

void Panel::centerText(int y, const std::string& label)
{
    if (not label.empty()) {
        int x = (maxX() - label.size()) / 2;
        if (x<0) {
            x=0;
        }
        writeStringAtPos({y, x}, label.c_str());
    }
}

void Panel::label(const std::string& topLabel, const std::string& bottomLabel)
{
    if (not topLabel.empty()) {
        centerText(0, topLabel);
    }
    if (not bottomLabel.empty()) {
        centerText(maxY(), bottomLabel);
    }
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

}
}
