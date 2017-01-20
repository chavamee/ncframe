#ifndef NCURSES_COMPONENT_BINDIGNS_H_
#define NCURSES_COMPONENT_BINDIGNS_H_

#include "common/platform.h"
#include "ncf/Window.hpp"
#include "ncf/Geometry.hpp"
#include <vector>
#include <memory>

//TODO: Should we add a non-owning variant of Draw?

class Component {
    public:
        Component() = default;

        Component(Component* parent) :
            parent(parent)
        {
        }

        virtual ~Component()
        {
        }

        virtual void bounds(Rect& bounds)
        {
            NCF_UNUSED(bounds);
        }

        virtual void intersects(const Point& point)
        {
            NCF_UNUSED(point);
        }

        virtual void draw(std::unique_ptr<Window> window = {}, std::unique_ptr<Window> subWindow = {}) = 0;

        virtual void add(Component* component, unsigned int pos = 0)
        {
            NCF_UNUSED(component);
            NCF_UNUSED(pos);
        }

        virtual void remove(Component* component)
        {
            NCF_UNUSED(component);
        }


        virtual Component* child(unsigned int pos)
        {
            NCF_UNUSED(pos);
            return nullptr;
        }

        virtual unsigned int childCount()
        {
            return 0;
        }

        Component* parent = nullptr;
};

#endif