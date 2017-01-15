#include "ncurses/Layouts.hpp"
#include <cassert>

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

void RowLayout::Draw(std::unique_ptr<Window> mainWindow)
{
    MaxHeight = mainWindow->Height();
    MaxWidth = mainWindow->Width();
    Show();
}

void RowLayout::Show()
{
    Compositor->Compose();
}

void RowLayout::Add(Component* component, unsigned int pos)
{
    m_components.insert(m_components.begin()+pos, component);
}

void RowLayout::Remove(Component* component)
{
    m_components.erase(std::find(m_components.begin(), m_components.end(), component));
}

Component* RowLayout::Child(int pos)
{
    return m_components.at(pos);
}

int RowLayout::ChildCount()
{
    return m_components.size();
}

UniformRowCompositor::UniformRowCompositor()
{
}

UniformRowCompositor::~UniformRowCompositor()
{
}

void UniformRowCompositor::Compose()
{
    RowLayout* composition = static_cast<RowLayout*>(Composition);
    if (composition == nullptr) {
        throw std::runtime_error("Invalid composition");
    }

    unsigned int maxHeight = composition->MaxHeight;
    unsigned int maxWidth = composition->MaxWidth;

    int numCmps = composition->ChildCount();
    int cmpWidth = maxWidth / numCmps;
    int currentX = 0;

    for (int i = 0; i < numCmps; i++) {
        m_row.Add(composition->Child(i));
        composition->Child(i)->Draw(std::make_unique<Window>(maxHeight, cmpWidth, 0, currentX));
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

void ColumnLayout::Draw(std::unique_ptr<Window> mainWindow)
{
    MaxHeight = mainWindow->Height();
    MaxWidth = mainWindow->Width();
    Show();
}

void ColumnLayout::Show()
{
    Compositor->Compose();
}

void ColumnLayout::Add(Component* component, unsigned int pos)
{
    m_components.insert(m_components.begin()+pos, component);
}

void ColumnLayout::Remove(Component* component)
{
    m_components.erase(std::find(m_components.begin(), m_components.end(), component));
}

Component* ColumnLayout::Child(int pos)
{
    return m_components.at(pos);
}

int ColumnLayout::ChildCount()
{
    return m_components.size();
}

UniformColumnCompositor::UniformColumnCompositor()
{
}

UniformColumnCompositor::~UniformColumnCompositor()
{
}

void UniformColumnCompositor::Compose()
{
    ColumnLayout* composition = static_cast<ColumnLayout*>(Composition);

    unsigned int maxHeight = composition->MaxHeight;
    unsigned int maxWidth = composition->MaxWidth;
    int numCmps = composition->ChildCount();
    int cmpHeight = maxHeight / numCmps;
    int currentY = 0;

    for (int i = 0; i < numCmps; i++) {
        m_column.Add(composition->Child(i));
        composition->Child(i)->Draw(std::make_unique<Window>(cmpHeight, maxWidth, currentY, 0));
        currentY += cmpHeight;

    }
}
