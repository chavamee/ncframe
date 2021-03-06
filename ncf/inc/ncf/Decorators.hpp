#ifndef NCF_DECORATORS_H
#define NCF_DECORATORS_H

#include "ncf/Component.hpp"

namespace ncf {

class Decorator : public Component {
    public:
        Decorator(Component* component) :
            m_component(component)
        {
        }

        void draw(std::unique_ptr<Window> window = {}, std::unique_ptr<Window> subWindow = {}) override
        {
            m_component->draw(std::move(window), std::move(subWindow));
        }

    private:
        Component* m_component = nullptr;
};

class Border : public Decorator {
    public:
        Border(Component* component) :
            Decorator(component)
        {
        }
        void draw(std::unique_ptr<Window> window = {}, std::unique_ptr<Window> subWindow = {}) override
        {
            window->drawBorder();
            Decorator::draw(std::move(window), std::move(subWindow));
        }
};

}

#endif /* ifndef NCURSES_DECORATORS_H_ */
