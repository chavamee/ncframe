#ifndef NCURSES_WINDOW_BINDINGS_H_
#define NCURSES_WINDOW_BINDINGS_H_

extern "C" {
#include <curses.h>
#include <panel.h>
}

#include "ncf/Geometry.hpp"
#include "common/defcurs.h"

#include <functional>
#include <memory>
#include <iostream>


class Window;

//TODO: make attribute a struct/class to use RAII to reset attron/attroff
//TODO: implement interface for all window functionality that needs to be
//      exposed in Window class
//
//TODO: Make int y, int x pairs to Point structs
//TODO: Complete panel implementation

class Window {
    friend Window;

    public:
        /**
         * Defualt constructor
         */
        Window();

        //TODO: Should we take ownership of win?
        /**
         * Construct a Window object off of a ncurses WINDOW handle
         */
        Window(WINDOW* win);

        /**
         * Construct a new window
         *
         * @param height height of the window
         * @param width  width of the window
         * @param y      y coordinate of the window origin
         * @param x      x coordinate of the window origin
         */
        Window(
                int height,
                int width,
                int y = 0,
                int x = 0
              );

        Window(
                const Rect& rect
              );

        /**
         * Construct a new window with a parent window
         *
         * @param parent parent window of this window.
         *               The window becomes a sub window of parent
         * @param height height of the window
         * @param width  width of the window
         * @param y      y coordinate of the window origin
         * @param x      x coordinate of the window origin
         */
        Window( Window& parent,
                int height,
                int width,
                int y = 0,
                int x = 0,
                bool derived = false
              );


        Window(const Window& rhs) :
            m_handle(rhs.m_handle),
            m_parent(rhs.m_parent),
            m_subWins(rhs.m_subWins),
            m_sib(rhs.m_sib),
            m_isOwner(rhs.m_isOwner)
        {
        }

        Window(Window&& rhs) :
            m_handle(rhs.m_handle),
            m_parent(rhs.m_parent),
            m_subWins(rhs.m_subWins),
            m_sib(rhs.m_sib),
            m_isOwner(rhs.m_isOwner)
        {
            rhs.m_handle = NULL;
        }

        //TODO; If we used the ncurses window handle constructor
        //      and we do not take ownership we should not delete
        //      the handle
        /**
         * Window destructor
         */
        virtual ~Window();

        //int            tabsize() const { initialize(); return TABSIZE; }
        // Size of a tab on terminal, *not* window

        static int     numberOfColors();
        // Number of available colors

        /**
         * Returns the number of available for this window
         * @return the number of colors
         */
        int colors() const { return numberOfColors(); }

        // -------------------------------------------------------------------------
        // window status
        // -------------------------------------------------------------------------

        int getCursorX() const { return getcurx(m_handle); }
        // Column of top left corner relative to stdscr

        int getCursorY() const { return getcury(m_handle); }
        // Line of top left corner relative to stdscr

        //TODO: Return color struct
        /*NCURSES_PAIRS_T getcolor() const;
        // Actual color pair

        NCURSES_COLOR_T Foreground() const { return getcolor(0); }
        // Actual foreground color

        NCURSES_COLOR_T Background() const { return getcolor(1); }
        // Actual background color*/

        // -------------------------------------------------------------------------
        // window positioning
        // -------------------------------------------------------------------------
        // TODO: Do we need this if we are mergin panel with window and using move_panel?
        /*int Move(int begin_y, int begin_x) {
            return ::mvwin(m_handle, begin_y, begin_x); }*/
        // Move window to new position with the new position as top left corner.

        // -------------------------------------------------------------------------
        // coordinate positioning
        // -------------------------------------------------------------------------
        int moveCursor(int y, int x) { return ::wmove(m_handle, y, x); }
        // Move cursor the this position. Only moves cursor on virtual screen and
        // needs refresh to update position in physical screen

        Point getCursorPosition() const;
        // Get current position of the cursor

        Point getOriginPoint() const;
        // Get beginning of the window

        int size() const;
        // Get size of the window

        int moveCursorImmediately(int oldrow, int oldcol, int newrow, int newcol) const {
            return ::mvcur(oldrow, oldcol, newrow, newcol); }
        // Perform lowlevel cursor motion that takes effect immediately.

        // -------------------------------------------------------------------------
        // input
        // -------------------------------------------------------------------------
        //TODO: Return of GetKeyStroke should probably have alias/user type
        int getKeystroke() { return ::wgetch(m_handle); }
        // Get a keystroke from the window.

        int  getKeyStrokeFromPos(int y, int x) { return mvwgetch(m_handle, y, x); }
        // Move cursor to position and get a keystroke from the window

        int  getline(std::string& str, int n=-1);
        // Read a series of characters into str until a newline or carriage return
        // is received. Read at most n characters. If n is negative, the limit is
        // ignored.

        int getlineFromPos(int y, int x, std::string& str, int n=-1);
        // Move the cursor to the requested position and then perform the getstr()
        // as described above.

        int extractString(std::string& str, int n=-1);
        // Get a string of characters from the window into the buffer s. Retrieve
        // at most n characters, if n is negative retrieve all characters up to the
        // end of the current line. Attributes are stripped from the characters.

        int extractStringFromPos(int y, int x, std::string& s, int n=-1);
        // Move the cursor to the requested position and then perform the instr()
        // as described above.

        int            scanw(const char* fmt, ...);
            // Perform a scanw function from the window.

        int            scanw(const char*, va_list);
        // Perform a scanw function from the window.

        int            scanw(int y, int x, const char* fmt, ...);
            // Move the cursor to the requested position and then perform a scanw
            // from the window.

        int            scanw(int y, int x, const char* fmt, va_list);
        // Move the cursor to the requested position and then perform a scanw
        // from the window.

        // -------------------------------------------------------------------------
        // output
        // -------------------------------------------------------------------------
        int putChr(const chtype ch) { return ::waddch(m_handle, ch); }
        // Put attributed character to the window.

        int putChrAtPos(int y, int x, const chtype ch) {
            return mvwaddch(m_handle, y, x, ch); }
        // Move cursor to the requested position and then put attributed character
        // to the window.

        virtual int echoChar(const chtype ch) { return ::wechochar(m_handle, ch); }
        // Put attributed character to the window and refresh it immediately.

        int writeString(const std::string& str, int n=-1) {
            return ::waddnstr(m_handle, str.c_str(), n);
        }
        // Write the string str to the window, stop writing if the terminating
        // NUL or the limit n is reached. If n is negative, it is ignored.

        int writeStringAtPos(int y, int x, const std::string& str, int n=-1) {
            return mvwaddnstr(m_handle, y, x, str.c_str(), n);
        }
        // Move the cursor to the requested position and then perform the addchstr
        // as described above.

        //namspace lowlevel {
        /*int            addchstr(const chtype* str, int n=-1) {
            return ::waddchnstr(m_handle, str, n); }
        // Write the string str to the window, stop writing if the terminating
        // NUL or the limit n is reached. If n is negative, it is ignored.

        int            addchstr(int y, int x, const chtype * str, int n=-1) {
            return ::mvwaddchnstr(m_handle, y, x, str, n); }
        // Move the cursor to the requested position and then perform the addchstr
        // as described above.
        //}*/

        int print(const char* fmt, ...)
            // Do a formatted print to the window.
#if (__GNUG__ >= 2) && !defined(printf)
            __attribute__ ((format (printf, 2, 3)));
#else
        ;
#endif

        int printAt(int y, int x, const char * fmt, ...)
            // Move the cursor and then do a formatted print to the window.
#if (__GNUG__ >= 2) && !defined(printf)
            __attribute__ ((format (printf, 4, 5)));
#else
        ;
#endif

        chtype getChrOnCursor() const { return ::winch(m_handle); }
        // Retrieve attributed character under the current cursor position.

        chtype getChrAtPos(int y, int x) { return mvwinch(m_handle, y, x); }
        // Move cursor to requested position and then retrieve attributed character
        // at this position.

        int getStr(chtype* str, int n=-1) {
            return ::winchnstr(m_handle, str, n);
        }
        // Read the string str from the window, stop reading if the terminating
        // NUL or the limit n is reached. If n is negative, it is ignored.

        int getStrAtPos(int y, int x, chtype* str, int n=-1);
        // Move the cursor to the requested position and then perform the inchstr
        // as described above.

        int insertChar(chtype ch) { return ::winsch(m_handle, ch); }
        // Insert attributed character into the window before current cursor
        // position.

        int insertCharAtPos(int y, int x, chtype ch) {
            return mvwinsch(m_handle, y, x, ch);
        }
        // Move cursor to requested position and then insert the attributed
        // character before that position.

        int insertLine(int n=1) {
            return n > 0 ? ::winsdelln(m_handle, n) : 0;
        }

        int deleteLine(int n=-1) {
            return n < 0 ? ::winsdelln(m_handle, n) : 0;
        }

        int insertStr(const char *s, int n=-1) {
            return ::winsnstr(m_handle, s, n); }
        // Insert the string into the window before the current cursor position.
        // Insert stops at end of string or when the limit n is reached. If n is
        // negative, it is ignored.

        int insertStrAtPos(int y, int x, const char *s, int n=-1) {
            return mvwinsnstr(m_handle, y, x, s, n); }
        // Move the cursor to the requested position and then perform the insstr()
        // as described above.

        // TODO: Make custom type for methods that manipulate attributes
        int setAttribute(chtype at) { return wattrset(m_handle, static_cast<int>(at)); }
        // Set the window attributes;

        chtype getAttributes() { return getattrs(m_handle); }
        // Get the window attributes;
        // TODO: Change to struct or other representation

        int setColor(NCURSES_PAIRS_T color_pair_number, void* opts=NULL) {
            return ::wcolor_set(m_handle, color_pair_number, opts); }
        // Set the window color attribute;

        int charAttribute(int n, attr_t attr, NCURSES_PAIRS_T color, const void *opts=NULL) {
            return ::wchgat(m_handle, n, attr, color, opts); }
        // Change the attributes of the next n characters in the current line. If
        // n is negative or greater than the number of remaining characters in the
        // line, the attributes will be changed up to the end of the line.

        int charAttributeAtPos(int y, int x,
                int n, attr_t attr, NCURSES_PAIRS_T color, const void *opts=NULL) {
            return mvwchgat(m_handle, y, x, n, attr, color, opts); }
        // Move the cursor to the requested position and then perform chgat() as
        // described above.

        // -------------------------------------------------------------------------
        // background
        // -------------------------------------------------------------------------
        chtype getBackgroundAttributes() const { return getbkgd(m_handle); }
        // Get current background setting.

        int    setBackgroundAttributes(const chtype ch) { return wbkgd(m_handle, ch); }
        // Set the background property and apply it to the window.

        // TODO: This is for stdcr and should be defined in the globals
        //void bkgdset(chtype ch) { ::wbkgdset(m_handle, ch); }
        // Set the background property.

        // -------------------------------------------------------------------------
        // borders
        // -------------------------------------------------------------------------
        int box(chtype vert=0, chtype  hor=0) {
            return ::wborder(m_handle, vert, vert, hor, hor, 0, 0, 0, 0); }
        // Draw a box around the window with the given vertical and horizontal
        // drawing characters. If you specify a zero as character, curses will try
        // to find a "nice" character.

        int border(chtype left=0, chtype right=0,
                chtype top =0, chtype bottom=0,
                chtype top_left =0, chtype top_right=0,
                chtype bottom_left =0, chtype bottom_right=0) {
            return ::wborder(m_handle, left, right, top, bottom, top_left, top_right,
                    bottom_left, bottom_right); }
        // Draw a border around the window with the given characters for the
        // various parts of the border. If you pass zero for a character, curses
        // will try to find "nice" characters.

        // -------------------------------------------------------------------------
        // lines and boxes
        // -------------------------------------------------------------------------
        int horizontalLine(int len, chtype ch=0) { return ::whline(m_handle, ch, len); }
        // Draw a horizontal line of len characters with the given character. If
        // you pass zero for the character, curses will try to find a "nice" one.

        int horizontalLineAt(int y, int x, int len, chtype ch=0) {
            return mvwhline(m_handle, y, x, ch, len); }
        // Move the cursor to the requested position and then draw a horizontal line.

        int verticalLine(int len, chtype ch=0) { return ::wvline(m_handle, ch, len); }
        // Draw a vertical line of len characters with the given character. If
        // you pass zero for the character, curses will try to find a "nice" one.

        int verticalLineAt(int y, int x, int len, chtype ch=0) {
            return mvwvline(m_handle, y, x, ch, len); }
        // Move the cursor to the requested position and then draw a vertical line.

        // -------------------------------------------------------------------------
        // erasure
        // -------------------------------------------------------------------------
        int erase() { return ::werase(m_handle); }
        // Erase the window.

        int clear() { return ::wclear(m_handle); }
        // Clear the window.

        int setClearOkFlag(bool bf) { return ::clearok(m_handle, bf); }
        // Set/Reset the clear flag. If set, the next refresh() will clear the
        // screen.

        int clearBottom() { return ::wclrtobot(m_handle); }
        // Clear to the end of the window.

        int clearToEndOfLine() { return ::wclrtoeol(m_handle); }
        // Clear to the end of the line.

        int deleteCharUnderCursor() { return ::wdelch(m_handle); }
        // Delete character under the cursor.

        int deleteCharAtPos(int y, int x) { return mvwdelch(m_handle, y, x); }
        // Move cursor to requested position and delete the character under the
        // cursor.

        int deleteCurrentLine() { return ::winsdelln(m_handle, -1); }
        // Delete the current line.

        // -------------------------------------------------------------------------
        // screen control
        // -------------------------------------------------------------------------
        int scroll(int amount=1) { return ::wscrl(m_handle, amount); }
        // Scroll amount lines. If amount is positive, scroll up, otherwise
        // scroll down.

        int  setScrollOkFlag(bool bf) { return ::scrollok(m_handle, bf); }
        // If bf is TRUE, window scrolls if cursor is moved off the bottom
        // edge of the window or a scrolling region, otherwise the cursor is left
        // at the bottom line.

        int setSoftScrollingRegion(int from, int to) {
            return ::wsetscrreg(m_handle, from, to); }
        // Define a soft scrolling region.

        int setLineModefyMode(bool bf) { return ::idlok(m_handle, bf); }
        // If bf is TRUE, use insert/delete line hardware support if possible.
        // Otherwise do it in software.

        void setCharacterModifyMode(bool bf) { ::idcok(m_handle, bf); }
        // If bf is TRUE, use insert/delete character hardware support if possible.
        // Otherwise do it in software.

        int  touchLine(int s, int c) { return ::touchline(m_handle, s, c); }
        // Mark the given lines as modified.

        int touch()   { return ::wtouchln(m_handle, 0, height(), 1); }
        // Mark the whole window as modified.

        int untouch() { return ::wtouchln(m_handle, 0, height(), 0); }
        // Mark the whole window as unmodified.

        int touchLine(int s, int cnt, bool changed=TRUE) {
            return ::wtouchln(m_handle, s, cnt, static_cast<int>(changed ? 1 : 0)); }
        // Mark cnt lines beginning from line s as changed or unchanged, depending
        // on the value of the changed flag.

        bool isLineTouched(int line) const {
            return (::is_linetouched(m_handle, line) ? TRUE:FALSE); }
        // Return TRUE if line is marked as changed, FALSE otherwise

        bool isTouched() const {
            return (::is_wintouched(m_handle) ? TRUE:FALSE); }
        // Return TRUE if window is marked as changed, FALSE otherwise

        int setLeaveCursor(bool bf) { return ::leaveok(m_handle, bf); }
        // If bf is TRUE, curses will leave the cursor after an update whereever
        // it is after the update.

        int  redrawLines(int from, int n) { return ::wredrawln(m_handle, from, n); }
        // Redraw n lines starting from the requested line

        int  redraw() { return ::wredrawln(m_handle, 0, height()); }
        // Redraw the whole window

        int            doupdate()  { return ::doupdate(); }
        // Do all outputs to make the physical screen looking like the virtual one

        void syncDown()  { ::wsyncdown(m_handle); }
        // Propagate the changes down to all descendant windows

        void syncUp()    { ::wsyncup(m_handle); }
        // Propagate the changes up in the hierarchy

        void syncCursorUp() { ::wcursyncup(m_handle); }
        // Position the cursor in all ancestor windows corresponding to our setting

        int enableSync(bool bf) { return ::syncok(m_handle, bf); }
        // If called with bf=TRUE, syncup() is called whenever the window is changed

        void enableImmediate(bool bf) { ::immedok(m_handle, bf); }
        // If called with bf=TRUE, any change in the window will cause an
        // automatic immediate refresh()

        int intrflush(bool bf) { return ::intrflush(m_handle, bf); }

        int enableKeypad(bool bf) { return ::keypad(m_handle, bf); }
        // If called with bf=TRUE, the application will interpret function keys.

        int enableNoDelay(bool bf) { return ::nodelay(m_handle, bf); }

        int enableMeta(bool bf) { return ::meta(m_handle, bf); }
        // If called with bf=TRUE, keys may generate 8-Bit characters. Otherwise
        // 7-Bit characters are generated.

        int enableStandout() { return wstandout(m_handle); }
        // Enable "standout" attributes

        int disableStandout() { return wstandend(m_handle); }
        // Disable "standout" attributes
        //
        int enableStandout(bool bf) { return bf ? wstandout(m_handle) : wstandend(m_handle); }

        virtual int refresh() { return ::wrefresh(m_handle); }
        // Propagate the changes in this window to the virtual screen and call
        // doupdate(). This is redefined in NCursesPanel.

        virtual int  noutrefresh() { return ::wnoutrefresh(m_handle); }
        // Propagate the changes in this window to the virtual screen. This is
        // redefined in NCursesPanel.


        // -------------------------------------------------------------------------
        // multiple window control
        // -------------------------------------------------------------------------
        int overlay(Window& win) {
            return ::overlay(m_handle, win.m_handle); }
        // Overlay this window over win.

        int overwrite(Window& win) {
            return ::overwrite(m_handle, win.m_handle); }
        // Overwrite win with this window.

        int copy(Window& win,
                int sminrow, int smincol,
                int dminrow, int dmincol,
                int dmaxrow, int dmaxcol, bool overlaywin=TRUE) {
            return ::copywin(m_handle, win.m_handle, sminrow, smincol, dminrow, dmincol,
                    dmaxrow, dmaxcol, static_cast<int>(overlaywin ? 1 : 0)); }
        // Overlay or overwrite the rectangle in win given by dminrow,dmincol,
        // dmaxrow,dmaxcol with the rectangle in this window beginning at
        // sminrow,smincol.

        // -------------------------------------------------------------------------
        // Extended functions
        // -------------------------------------------------------------------------
#if defined(NCURSES_EXT_FUNCS) && (NCURSES_EXT_FUNCS != 0)
        int            wresize(int newLines, int newColumns) {
            return ::wresize(m_handle, newLines, newColumns); }
#endif

        // -------------------------------------------------------------------------
        // Mouse related
        // -------------------------------------------------------------------------
        bool hasMouse() const;
        // Return TRUE if terminal supports a mouse, FALSE otherwise


        int height() const { return maxY() + 1; }

        int width() const { return maxX() + 1; }

        int originX() const { return getbegx(m_handle); }

        int originY() const { return getbegy(m_handle); }

        int currentX() const { return getcurx(m_handle); }

        int currentY() const { return getcury(m_handle); }

        void top();

        void bottom();

        void show();

        void hide();

        bool isHidden()
        {
            return ::panel_hidden(m_panel);
        }

        void move(int x, int y);

        //TODO: Resize()

        //Window* WhichAbove();

        //Window* WhichBelow();


        int maxX() const
        {
            return getmaxx(m_handle) == ERR ? ERR : getmaxx(m_handle)-1;
        }

        int maxY() const
        {
            return getmaxy(m_handle) == ERR ? ERR : getmaxy(m_handle)-1;
        }

        int setPalette(short fore, short back, short pair);

        int setPalette(short fore, short back);

        //int SetColor(short pair);

        void attributeOn(int attr)
        {
            wattron(m_handle, attr);
        }

        void attributeOff(int attr)
        {
            wattroff(m_handle, attr);
        }

        void frame()
        {
            ::box(m_handle, 0, 0);
        }

        void printStr(const std::string& str);


        bool isDescendant(Window& win);
        // Return TRUE if win is a descendant of this.

        Point getParentPoint() const {
            int x = 0;
            int y = 0;
            ::getparyx(m_handle, y, x);
            return Point{x, y};
        }
        // Get parent's beginning of the window
        //
        // -------------------------------------------------------------------------
        // traversal support
        // -------------------------------------------------------------------------
        Window*  child() { return m_subWins; }
        // Get the first child window.

        Window*  sibling() { return m_sib; }
        // Get the next child of my parent.

        Window*  parent() { return m_parent; }
        // Get my parent.

        WINDOW* getHandle() const
        {
            return m_handle;
        }

        short getPair() const;

    protected:
        WINDOW* m_handle = NULL;
        PANEL* m_panel = NULL;


        Window* m_parent  = nullptr;   // parent, if subwindow
        Window* m_subWins = nullptr;   // head of subwindows list
        Window* m_sib     = nullptr;   // next subwindow of parent

    private:
        void _killSubwindows();
        bool m_isOwner = true;

};

#endif
