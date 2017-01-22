#include "ncf/Layout.hpp"
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
