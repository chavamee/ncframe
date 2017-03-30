#include "ncf/Column.hpp"

using namespace std;

namespace ncf {

Column::Column()
{
}

Column::Column(const Rect& rect) :
    Widget { rect }
{
}

Column::~Column()
{
}

void Column::draw(unique_ptr<ncurses::Window> window, unique_ptr<ncurses::Window> subWindow)
{
    size_t numCmps = childCount();
    int cmpHeight = maxHeight / numCmps;
    int currentY = 0;

    for (size_t i = 0; i < numCmps; i++) {
        child(i)->draw(make_unique<ncurses::Window>(cmpHeight, maxWidth, currentY, 0));
        currentY += cmpHeight;
    }
}

void Column::add(Component* component, unsigned int pos)
{
    m_components.insert(m_components.begin()+pos, component);
}

void Column::remove(Component* component)
{
    m_components.erase(std::find(m_components.begin(), m_components.end(), component));
}

Component* Column::child(std::size_t pos)
{
    return m_components.at(pos);
}

std::size_t Column::childCount()
{
    return m_components.size();
}

}
