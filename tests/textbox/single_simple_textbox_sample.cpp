#include <ncf/Application.hpp>
#include <ncf/TextBox.hpp>

using namespace ncf;

int main(void)
{
    Application app;

    TextBox box;

    box.setText("Hello, World!");
    box.draw();

    app.start();

    return 0;
}
