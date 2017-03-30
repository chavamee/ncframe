#ifndef NCF_NCURSES_ROW_H_
#define NCF_NCURSES_ROW_H_

#include "ncf/Widget.hpp"

#include <algorithm>

namespace ncf {

class Row : public Widget {
    public:
        Row();

        Row(const Rect& rect);

        ~Row();

        void draw(std::unique_ptr<ncurses::Window> window = {}, std::unique_ptr<ncurses::Window> subWindow = {}) override;

        void add(Component* component, unsigned int pos = 0) override;

        void remove(Component* component) override;

        Component* child(std::size_t pos) override;

        size_t childCount() override;

        size_t maxHeight = LINES - 1;
        size_t maxWidth  = COLS - 1;

    private:
        std::vector<Component*> m_components;
};

}
#endif
