#include "ncf/Row.hpp"
#include "ncf/Panel.hpp"

using namespace std;

namespace ncf {

Row::Row()
{
}

Row::Row(const Rect& rect) :
    Widget { rect }
{
}

Row::~Row()
{
}

void Row::draw(unique_ptr<Window> window, unique_ptr<Window> subWindow)
{
    if (window) {
        maxHeight = window->height();
    }
    size_t numCmps = childCount();
    int cmpWidth = maxWidth / numCmps;
    int currentX = 0;

    for (size_t i = 0; i < numCmps; i++) {
        child(i)->draw(make_unique<Panel>(maxHeight, cmpWidth, 0, currentX));
        currentX += cmpWidth;
    }

    if (window) {
        setWindow(std::move(window));
    }
}

void Row::add(Component* component, unsigned int pos)
{
    m_components.insert(m_components.begin()+pos, component);
}

void Row::remove(Component* component)
{
    m_components.erase(std::find(m_components.begin(), m_components.end(), component));
}

Component* Row::child(std::size_t pos)
{
    return m_components.at(pos);
}

std::size_t Row::childCount()
{
    return m_components.size();
}

}
