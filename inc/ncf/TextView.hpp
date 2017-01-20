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

        TextView(const Rect& rect);

        virtual ~TextView()
        {
        }

        void draw(std::unique_ptr<Window> window = {}, std::unique_ptr<Window> subWindow = {}) override;

        int onKeyEvent(int ch) override;

        void onMouseEvent(int ch) override;

        bool onEvent(int ch) override;

    private:
        std::string m_content;
};

#endif /* ifndef NCURSES_TEXTVIEW_COMPONENT */
