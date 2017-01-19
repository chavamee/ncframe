#ifndef NCURSES_TEXTVIEW_COMPONENT
#define NCURSES_TEXTVIEW_COMPONENT value

#include "ncf/Component.hpp"
#include "ncf/Window.hpp"
#include "ncf/View.hpp"
#include <string>

//Should probably be widget
class TextView : public View {
    public:
        TextView();

        TextView(int height, int width);

        TextView(int height, int width, int y, int x);

        virtual ~TextView()
        {
        }

        void Draw(std::unique_ptr<Window> window = {}, std::unique_ptr<Window> subWindow = {}) override;

        int OnKeyEvent(int ch) override;

        void OnMouseEvent(int ch) override;

        bool OnEvent(int ch) override;

    private:
        std::string m_content;
};

#endif /* ifndef NCURSES_TEXTVIEW_COMPONENT */
