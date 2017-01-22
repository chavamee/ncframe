#include "ncf/Column.hpp"

using namespace std;

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

void Column::draw(unique_ptr<Window> window, unique_ptr<Window> subWindow)
{
    size_t numCmps = childCount();
    int cmpHeight = maxHeight / numCmps;
    int currentY = 0;

    for (size_t i = 0; i < numCmps; i++) {
        unique_ptr<Window> window = make_unique<Window>(cmpHeight, maxWidth, currentY, 0);
        child(i)->draw(std::move(window));
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

