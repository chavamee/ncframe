# NCFrame - NCurses C++ Framework

## Motivation
NCFframe aims to facilitate NCurses based application development by providing a Qt inspired framework on top of NCurses. It provides common interfaces for widget construction and terminal events.

## Example

### Create a menu

#### NCFrame

```cpp
#include <ncf/Application.hpp>
#include <ncf/Menu.hpp>

using namespace ncf;

int main(void)
{
  Application app;

  Menu menu {
    new Menu::Item {"Vim",    "A highly configurable text editor"},
    new Menu::Item {"Nano",   "The GNU Nano"},
    new Menu::Item {"Emacs",  "An extensible, customizable, free/libre text editor"},
    new Menu::Item {"Sublime","The text editor you'll fall in love with"},
    new Menu::Item {"Atom",   "A hackable editor for the 21st Century"},
    new Menu::Item {"Gedit",  "The GNOME text editor"}
  };

  menu.draw();

  app.start();

  return 0;
}
```

#### NCurses only
```cpp
/*
 * Example taken from http://www.tldp.org/HOWTO/NCURSES-Programming-HOWTO/menus.html#MENUWINDOWS
 */
#include <menu.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

char *choices[] = {
  "Vim",
  "Nano",
  "Emacs",
  "Sublime",
  "Atom",
  "Gedit",
  (char *)NULL
};

char *descriptions[] = {
  "A highly configurable text editor",
  "The GNU Nano",
  "An extensible, customizable, free/libre text editor",
  "The text editor you'll fall in love with",
  "A hackable editor for the 21st Century",
  "The GNOME text editor",
  (char *)NULL
};

int main()
{
  ITEM **my_items;
  int c;
  MENU *my_menu;
  WINDOW *my_menu_win;
  int n_choices, i;

  initscr();
  start_color();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  init_pair(1, COLOR_RED, COLOR_BLACK);

  n_choices = ARRAY_SIZE(choices);
  my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));
  for(i = 0; i < n_choices; ++i) {
    my_items[i] = new_item(choices[i], descriptions[i]);
  }

  my_menu = new_menu((ITEM **)my_items);

  my_menu_win = newwin(10, 40, 4, 4);
  keypad(my_menu_win, TRUE);

  set_menu_win(my_menu, my_menu_win);
  set_menu_sub(my_menu, derwin(my_menu_win, 6, 38, 3, 1));

  set_menu_mark(my_menu, " * ");

  box(my_menu_win, 0, 0);
  refresh();

  post_menu(my_menu);
  wrefresh(my_menu_win);

  while((c = wgetch(my_menu_win)) != 'q')
  {
    switch(c) {
    case KEY_DOWN:
      menu_driver(my_menu, REQ_DOWN_ITEM);
      break;
		case KEY_UP:
      menu_driver(my_menu, REQ_UP_ITEM);
      break;
    }
    wrefresh(my_menu_win);
  }

  unpost_menu(my_menu);
  free_menu(my_menu);
  for(i = 0; i < n_choices; ++i) {
    free_item(my_items[i]);
  }
  endwin();
}
```

### Building
`cmake . && make`
