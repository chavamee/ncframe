#ifndef NCF_NCURSES_COLUMN_H_
#define NCF_NCURSES_COLUMN_H_

#include "ncf/Component.hpp"
#include <algorithm>

class Column : public Component {
    public:
        void draw(std::unique_ptr<Window> window, std::unique_ptr<Window> subWindow = {}) override
        {
            //TODO: This is wrong
            for (auto& cmp : m_components) {
                cmp->draw(std::move(window), std::move(subWindow));
            }
        }

        void add(Component* component, unsigned int pos = 0) override
        {
            m_components.insert(m_components.begin()+pos, component);
        }

        void remove(Component* component) override
        {
            m_components.erase(std::find(m_components.begin(), m_components.end(), component));
        }

        Component* child(std::size_t pos) override
        {
            return m_components.at(pos);
        }

        std::size_t childCount() override
        {
            return m_components.size();
        }

    private:
        std::vector<Component*> m_components;
};

#endif
