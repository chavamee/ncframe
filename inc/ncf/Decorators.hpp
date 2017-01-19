#ifndef NCURSES_DECORATORS_H_
#define NCURSES_DECORATORS_H_ value

#include "ncf/Component.hpp"

class Decorator : public Component {
    public:
        Decorator(Component* component) :
            m_component(component)
        {
        }

        void Draw(std::unique_ptr<Window> window = {}, std::unique_ptr<Window> subWindow = {}) override
        {
            m_component->Draw(std::move(window), std::move(subWindow));
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
        void Draw(std::unique_ptr<Window> window = {}, std::unique_ptr<Window> subWindow = {}) override
        {
            window->Frame();
            Decorator::Draw(std::move(window), std::move(subWindow));
        }
};

#endif /* ifndef NCURSES_DECORATORS_H_ */
