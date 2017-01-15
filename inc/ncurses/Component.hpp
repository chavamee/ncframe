#ifndef NCURSES_COMPONENT_BINDIGNS_H_
#define NCURSES_COMPONENT_BINDIGNS_H_

#include "ncurses/Window.hpp"
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
            (void)bounds;
        }

        //virtual void Intersects(const Points&);

        virtual ~Component() {}

        virtual void Draw(std::unique_ptr<Window> window = {}) = 0;

        virtual void Add(Component* component, unsigned int pos = 0)
        {
            (void)component;
            (void)pos;
        }

        virtual void Remove(Component* component)
        {
            (void)component;
        }


        virtual Component* Child(int pos)
        {
            (void)pos;
            return nullptr;
        }

        virtual int ChildCount()
        {
            return 0;
        }

        Component* Parent = nullptr;
};

#endif
