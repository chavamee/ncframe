#ifndef NCURSES_COMPONENT_BINDIGNS_H_
#define NCURSES_COMPONENT_BINDIGNS_H_

#include "common/platform.h"
#include "ncf/Window.hpp"
#include <vector>
#include <memory>

struct Rect
{
};

class Component {
    public:
        Component() = default;

        Component(Component* parent) :
            Parent(parent)
        {
        }

        virtual void Bounds(Rect& bounds)
        {
            NCF_UNUSED(bounds);
        }

        //TODO?: virtual void Intersects(const Points&);

        virtual ~Component() {}

        //TODO: Should we add a non-owning variant of Draw?

        virtual void Draw(std::unique_ptr<Window> window = {}, std::unique_ptr<Window> subWindow = {}) = 0;

        virtual void Add(Component* component, unsigned int pos = 0)
        {
            NCF_UNUSED(component);
            NCF_UNUSED(pos);
        }

        virtual void Remove(Component* component)
        {
            NCF_UNUSED(component);
        }


        virtual Component* Child(int pos)
        {
            NCF_UNUSED(pos);
            return nullptr;
        }

        virtual int ChildCount()
        {
            return 0;
        }

        Component* Parent = nullptr;
};

#endif
