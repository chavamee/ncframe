#ifndef NCF_NCURSES_COLUMNLAYOUT_H_
#define NCF_NCURSES_COLUMNLAYOUT_H_

#include "ncf/Layout.hpp"
#include "ncf/Column.hpp"

class ColumnLayout : public Layout {
    public:
        ColumnLayout();

        ColumnLayout(LayoutCompositor* compositor);

        ColumnLayout(
                unsigned int height,
                unsigned int width,
                LayoutCompositor* compositor
                );

        virtual ~ColumnLayout();

        void draw(std::unique_ptr<Window> window = {}, std::unique_ptr<Window> subWindow = {}) override;

        void show() override;

        void add(Component* component, unsigned int pos = 0) override;

        void remove(Component* component) override;

        Component* child(std::size_t pos) override;

        std::size_t childCount() override;

    private:
        std::vector<Component*> m_components;
};


class UniformColumnCompositor : public LayoutCompositor {
    public:
        UniformColumnCompositor();

        virtual ~UniformColumnCompositor();

        void compose() override;

    private:
        Column m_column;
};

#endif
