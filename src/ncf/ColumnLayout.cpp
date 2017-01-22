#include "ncf/ColumnLayout.hpp"

using namespace std;

ColumnLayout::ColumnLayout() : Layout(new UniformColumnCompositor()) { Compositor->Composition = this; } ColumnLayout::ColumnLayout(LayoutCompositor* compositor) : Layout(compositor) { Compositor->Composition = this; } ColumnLayout::ColumnLayout(
        unsigned int height,
        unsigned int width,
        LayoutCompositor* compositor
        ) :
    Layout(height, width, compositor == nullptr ? new UniformColumnCompositor() : compositor)
{
    Compositor->Composition = this;
}

ColumnLayout::~ColumnLayout()
{
}

void ColumnLayout::draw(unique_ptr<Window> window, unique_ptr<Window> subWindow)
{
    MaxHeight = window->height();
    MaxWidth = window->width();
    show();
}

void ColumnLayout::show()
{
    Compositor->compose();
}

void ColumnLayout::add(Component* component, unsigned int pos)
{
    m_components.insert(m_components.begin()+pos, component);
}

void ColumnLayout::remove(Component* component)
{
    m_components.erase(std::find(m_components.begin(), m_components.end(), component));
}

Component* ColumnLayout::child(std::size_t pos)
{
    return m_components.at(pos);
}

std::size_t ColumnLayout::childCount()
{
    return m_components.size();
}

UniformColumnCompositor::UniformColumnCompositor()
{
}

UniformColumnCompositor::~UniformColumnCompositor()
{
}

void UniformColumnCompositor::compose()
{
    ColumnLayout* composition = static_cast<ColumnLayout*>(Composition);

    unsigned int maxHeight = composition->MaxHeight;
    unsigned int maxWidth = composition->MaxWidth;
    size_t numCmps = composition->childCount();
    int cmpHeight = maxHeight / numCmps;
    int currentY = 0;

    for (size_t i = 0; i < numCmps; i++) {
        m_column.add(composition->child(i));
        unique_ptr<Window> window = make_unique<Window>(cmpHeight, maxWidth, currentY, 0);
        composition->child(i)->draw(std::move(window));
        currentY += cmpHeight;

    }
}
