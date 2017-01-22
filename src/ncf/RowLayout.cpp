#include "ncf/RowLayout.hpp"

using namespace std;

RowLayout::RowLayout() :
    Layout(new UniformRowCompositor())
{
    Compositor->Composition = this;
}

RowLayout::RowLayout(
        unsigned int height,
        unsigned int width
        ) :
    Layout(height, width, new UniformRowCompositor())
{
    Compositor->Composition = this;
}

RowLayout::RowLayout(
        unsigned int height,
        unsigned int width,
        LayoutCompositor* compositor
        ) :
    Layout(height, width, compositor)
{
    Compositor->Composition = this;
}

RowLayout::~RowLayout()
{
}

void RowLayout::draw(unique_ptr<Window> window, unique_ptr<Window> subWindow)
{
    MaxHeight = window->height();
    MaxWidth = window->width();
    show();
}

void RowLayout::show()
{
    Compositor->compose();
}

void RowLayout::add(Component* component, unsigned int pos)
{
    m_components.insert(m_components.begin()+pos, component);
}

void RowLayout::remove(Component* component)
{
    m_components.erase(std::find(m_components.begin(), m_components.end(), component));
}

Component* RowLayout::child(std::size_t pos)
{
    return m_components.at(pos);
}

std::size_t RowLayout::childCount()
{
    return m_components.size();
}

UniformRowCompositor::UniformRowCompositor()
{
}

UniformRowCompositor::~UniformRowCompositor()
{
}

void UniformRowCompositor::compose()
{
    RowLayout* composition = static_cast<RowLayout*>(Composition);
    if (composition == nullptr) {
        throw std::runtime_error("Invalid composition");
    }

    unsigned int maxHeight = composition->MaxHeight;
    unsigned int maxWidth = composition->MaxWidth;

    size_t numCmps = composition->childCount();
    int cmpWidth = maxWidth / numCmps;
    int currentX = 0;

    for (size_t i = 0; i < numCmps; i++) {
        m_row.add(composition->child(i));
        unique_ptr<Window> window = make_unique<Window>(maxHeight, cmpWidth, 0, currentX);
        composition->child(i)->draw(std::move(window));
        currentX += cmpWidth;

    }
}

