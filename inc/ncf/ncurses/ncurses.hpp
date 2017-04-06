#ifndef NCF_NCURSES_NCURSES_H
#define NCF_NCURSES_NCURSES_H

extern "C" {
#include <curses.h>
}

#include <utility>

namespace ncf {
namespace ncurses {

/**
 * NCurses char type alias.
 *
 * This type encompases normal and wide characters.
 */
using NCCharType = chtype;

/**
 * ColorPair ID
 */
using ColorPairID = short;
using ColorType = short;
using ColorPair = std::pair<ColorType, ColorType>;

struct Color {
};

struct Border {
    NCCharType left         = 0;
    NCCharType right        = 0;
    NCCharType top          = 0;
    NCCharType bottom       = 0;
    NCCharType top_left     = 0;
    NCCharType top_right    = 0;
    NCCharType bottom_left  = 0;
    NCCharType bottom_right = 0;
};

struct Attribute {
};

class NCString {
};

/**
 * Initialize ncurses
 */
inline void initialize()
{
    static bool isInitialized = false;
    if (!isInitialized) {
        ::initscr();
        isInitialized = true;
        if (::has_colors()) {
            ::start_color();
        }
        ::noecho();
        ::cbreak();
    }
}

/**
 * Number of lines on terminal.
 */
inline int lines() { return LINES; }

/**
 * Number of cols on terminal.
 */
inline int cols() { initialize(); return COLS; }

/**
 * Size of a tab on the terminal,
 */
inline int tabsize() { initialize(); return TABSIZE; }

/**
 * Returns the amount of available colors for all windows
 *
 * @return number of available colors
 */
inline int colorCount()
{
    initialize();
    return (has_colors() ? COLORS : 1);
}

}
}

#endif
