#include "ncf/TextView.hpp"

using namespace std;

TextView::TextView()
{
}

TextView::TextView(int height, int width) :
    View(height, width)
{
}

TextView::TextView(int height, int width, int y, int x) :
    View(height, width)
{
    (void)y;
    (void)x;
}

void TextView::Draw(unique_ptr<Window> window, unique_ptr<Window> subWindow)
{
    //std::unique_ptr<Window> subWindow = std::make_unique<Window>(
            //window->Height()-2, window->Width()-2, window->OriginY()+1, window->OriginX()+1);
    View::Draw(std::move(window), std::move(subWindow));
}

int TextView::OnKeyEvent(int ch)
{
    switch (ch) {
        case KEY_UP:break;
    }
    return 0;
}

void TextView::OnMouseEvent(int ch)
{
    (void)ch;
}

bool TextView::OnEvent(int ch)
{
    (void)ch;
    return false;
}
