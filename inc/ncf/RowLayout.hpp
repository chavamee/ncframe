#ifndef NCF_NCURSES_ROWLAYOUT_H_
#define NCF_NCURSES_ROWLAYOUT_H_

#include "ncf/Layout.hpp"
#include "ncf/Row.hpp"

class RowLayout : public Layout {
    public:
        RowLayout();

        RowLayout(unsigned int height, unsigned int width);

        RowLayout(unsigned int height, unsigned int width, LayoutCompositor* compositor);

        virtual ~RowLayout();

        void draw(std::unique_ptr<Window> window = {}, std::unique_ptr<Window> subWindow = {}) override;

        void show() override;

        void add(Component* component, unsigned int pos = 0) override;

        void remove(Component* component) override;

        Component* child(std::size_t pos) override;

        std::size_t childCount() override;

    private:
        std::vector<Component*> m_components;
};

class UniformRowCompositor : public LayoutCompositor {
    public:
        UniformRowCompositor();

        virtual ~UniformRowCompositor();

        void compose() override;

    private:
        Row m_row;
};

#endif
