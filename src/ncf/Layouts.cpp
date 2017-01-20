#include "ncf/Layouts.hpp"
#include <cassert>

using namespace std;

LayoutCompositor::LayoutCompositor()
{
}

LayoutCompositor::~LayoutCompositor()
{
}

Layout::Layout(LayoutCompositor* compositor) :
    Composition(compositor)
{
}

Layout::Layout(unsigned int height, unsigned int width, LayoutCompositor* compositor) :
    Composition(compositor),
    MaxHeight(height),
    MaxWidth(width)
{
}

Layout::~Layout()
{
}

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
    assert(compositor != nullptr);
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

Component* RowLayout::child(unsigned int pos)
{
    return m_components.at(pos);
}

unsigned int RowLayout::childCount()
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

    unsigned int numCmps = composition->childCount();
    int cmpWidth = maxWidth / numCmps;
    int currentX = 0;

    for (unsigned int i = 0; i < numCmps; i++) {
        m_row.add(composition->child(i));
        unique_ptr<Window> window = make_unique<Window>(maxHeight, cmpWidth, 0, currentX);
        composition->child(i)->draw(std::move(window));
        currentX += cmpWidth;

    }
}

ColumnLayout::ColumnLayout() :
    Layout(new UniformColumnCompositor())
{
    Compositor->Composition = this;
}

ColumnLayout::ColumnLayout(LayoutCompositor* compositor) :
    Layout(compositor)
{
    Compositor->Composition = this;
}

ColumnLayout::ColumnLayout(
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

Component* ColumnLayout::child(unsigned int pos)
{
    return m_components.at(pos);
}

unsigned int ColumnLayout::childCount()
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
    unsigned int numCmps = composition->childCount();
    int cmpHeight = maxHeight / numCmps;
    int currentY = 0;

    for (unsigned int i = 0; i < numCmps; i++) {
        m_column.add(composition->child(i));
        unique_ptr<Window> window = make_unique<Window>(cmpHeight, maxWidth, currentY, 0);
        composition->child(i)->draw(std::move(window));
        currentY += cmpHeight;

    }
}
