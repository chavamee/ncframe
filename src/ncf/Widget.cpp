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
