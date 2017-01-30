#include "ncf/Widget.hpp"
#include "ncf/Geometry.hpp"

std::vector<Widget*> Widget::WidgetList = {};

Widget::Widget()
{
    Widget::WidgetList.push_back(this);
}

Widget::Widget(const Rect& rect) :
    m_rect(rect)
{
}

void Widget::hide()
{
    if (m_window) {
        m_window->hide();
    }

    if (m_subWindow) {
        m_subWindow->hide();
    }

    //TODO: Should/can we send a redraw event?
}
