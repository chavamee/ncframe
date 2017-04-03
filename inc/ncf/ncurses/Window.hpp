#ifndef NCF_NCURSES_WINDOW_H
#define NCF_NCURSES_WINDOW_H

#include "ncf/ncurses/ncurses.hpp"
#include "ncf/Geometry.hpp"

#include <functional>
#include <memory>
#include <iostream>

namespace ncf {
namespace ncurses {

/**
 * Wrapper to an ncurses WINDOW object
 */
class Window {
    public:

    /**
     * Default Window constructor
     */
    Window();

    /**
     * Construct a Window object off of a ncurses WINDOW handle.
     *
     * @param win           ncurses WINDOW handle.
     *                      If the Window object takes ownership of the ncurses handle,
     *                      the win pointer is set to null.
     * @param takeOnwership Should this Window object take ownership of the ncurses handle?
     */
    Window(WINDOW*& win, bool takeOnwership = true);

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

    /**
     * Construct a new window
     *
     * @param rect rectangular geometry of the window
     */
    Window(
            const Rect& rect
          );

    /**
     * Construct a new window with a parent window
     *
     * @param parent   parent window for this window.
     *                 The window becomes a sub window of parent
     * @param height   height of the window
     * @param width    width of the window
     * @param y        y coordinate of the window origin
     * @param x        x coordinate of the window origin
     * @param relative If true, the origin is set relative to the parent window.
     *                 Otherwise the position is absolute and set relative to stdscr
     */
    Window( Window& parent,
            int height,
            int width,
            int y = 0,
            int x = 0,
            bool derived = false
          );

    /**
     * Construct a new window with a parent window
     *
     * @param parent   parent window of this window.
     *                 The window becomes a sub window of parent
     * @param rect     rectangular geometry of the window
     * @param relative If true, the origin is set relative to the parent window.
     *                 Otherwise the position is absolute and set relative to stdscr
     */
    Window(Window& parent,
           const Rect& rect,
           bool derived = false
          );

    /**
     * Copy constructor.
     *
     * The ncurses WINDOW handle is never copied over. Instead
     * the window is replicated with a new WINDOW handle.
     */
    Window(const Window& window) = delete;

    /**
     * Move constructor
     */
    Window(Window&& rhs);

    /**
     * Copy assignment operator.
     *
     * The ncurses WINDOW handle is never copied over. Instead
     * the window is replicated with a new WINDOW handle.
     */
    Window& operator=(Window& rhs) = delete;

    /**
     * Move assignment operator
     */
    Window& operator=(Window&& rhs);

    /**
     * Window destructor
     */
    virtual ~Window();

    //TODO: int            tabsize() const { initialize(); return TABSIZE; }
    // Size of a tab on terminal, *not* window

    /**
     * Returns the amount of available colors for all windows
     *
     * @return number of available colors
     */
    static int colorCount();

    /**
     * Returns the number of available colors for this window
     *
     * @return number of colors available
     */
    int colors() const { return colorCount(); }

    /**
     * Get actual color pair
     *
     * @return the effective color pair for this window
     */
    ColorPairID getColor() const;

    /**
     * Get actual foreground color
     *
     * @return the effective foreground color for this window.
     */
    ColorType foreground() const { return getColor(0); }

    /**
     * Get actual background color
     *
     * @return the effective background color for this window.
     */
    ColorType background() const { return getColor(1); }


    /**
     * Set color palette entry
     *
     * @param pair the color pair values to set for the current pair
     */
    void setPalette(ColorPair color);

    /**
     * Set actually used palette entry.
     *
     * @param pair Color pair id to use
     */
    void setColor(ColorPairID pair);

    /**
     * Move the cursor to the given point.
     *
     * Only moves the cursor on the virtual screen and needs a refresh to update
     * the psoition on the physical screen.
     *
     * @param point point to place the cursor at
     */
    void moveCursor(const Point& point) { return _onError (wmove(m_window, point.y, point.x)); }

    /**
     * Get the current position of the cursor
     *
     * @return the position of the cursor
     */
    Point getCursorPosition() const;

    /**
     * Get the beginning point of the window
     *
     * @return point of origin for this window
     */
    Point getOrigin() const;

    /**
     * Get the size of the window
     *
     * @return window size
     */
    Size size() const;

    /**
     * Perform low-level cursor motion that takes effect immediately.
     *
     * @param prevPoint previous position of cursor
     * @param newPoint  new position of cursor
     */
    void moveCursorImmediately(const Point& prevPoint, const Point& newPoint) {
        _onError ( mvcur(prevPoint.y, prevPoint.x, newPoint.y, newPoint.x) );
    }

    //TODO: Return of GetKeyStroke should probably have alias/user type
    //TODO: This can return ERR, check for it and throw appropriatetly
    /**
     * Get a keystroke from the window
     *
     * @return the key stroke read from the window
     */
    int getKeystroke() { return wgetch(m_window); }

    /**
     * Move the cursor and get a keystore from the window
     *
     * @return the key stroke read from the window
     */
    int  getKeyStrokeFromPos(const Point& pos) { return mvwgetch(m_window, pos.y, pos.x); }

    //TODO: getline functions and extractString functions should throw on error
    /**
     * Read a series of characters until a newline or carriage return is received.
     *
     * @param n read at most n characters. If n is negative, the limit is ignored.
     *
     * @return a string conatining the read characters.
     */
    std::string getline(int n=-1);

    /**
     * Move the cursor and read a line.
     *
     * This is equivalent to calling getline after moveCursor.
     *
     * @param n read at most n characters. If n is negative, the limit is ignored.
     *
     * @return a string conatining the read characters.
     */
    std::string getlineFromPos(const Point& ps, int n=-1);

    /**
     * Get a string from the window.
     *
     * Note that attributes are stripped from the characters.
     *
     * @param n read at most n characters. If n is negative, the limit is ignored.
     *
     * @return a string conatining the extracted characters.
     */
    std::string extractString(int n=-1);

    /**
     * Move the cursor and extract a string from the window.
     *
     * This is equivalent to calling extractStr after moveCursor.
     * Note that attributes are stripped from the characters.
     *
     * @param n read at most n characters. If n is negative, the limit is ignored.
     *
     * @return a string conatining the extracted characters.
     */
    std::string extractStringFromPos(const Point& pos, int n=-1);

    //TODO: Should throw on error ERR
    //TODO: Make these into variadic template functions
    //TODO: Docs for variants after variadic template function implementation
    /**
     * Perform a scanw operation on the window
     */
    void scan(const char* fmt, ...);

    /**
     * Move the cursor and perform a scanw operation on the window
     */
    void scan(const Point& pos, const char* fmt, ...);

    //TODO: Change ncCharType to something more expressive
    /**
     * Put attributed character to the window.
     */
    int putChr(const NCCharType ch) { return waddch(m_window, ch); }

    //TODO
    /**
     * Move the cursor and put attributed character to the window.
     */
    int putChrAtPos(Point& pos, const NCCharType ch) {
        return mvwaddch(m_window, pos.y, pos.x, ch);
    }

    /**
     * Put attributed character to the window and refresh it immediately.
     */
    virtual int echoChar(const NCCharType ch) { return wechochar(m_window, ch); }

    /**
     * Write a string to the window.
     *
     * Stop writing if the terminating null or the limit n is reached.
     *
     * @param str the string to write
     * @param n   number of characters to write up to
     */
    void writeString(const std::string& str, int n=-1) {
        _onError ( waddnstr(m_window, str.c_str(), n) );
    }

    /**
     * Move the cursor and then write a string to the window
     *
     * @param pos the position to move the cursor to
     * @param str the string to write
     */
    void writeStringAtPos(const Point& pos, const std::string& str) {
        _onError ( mvwaddnstr(m_window, pos.y, pos.x, str.c_str(), str.size()) );
    }

    //TODO:
    //namspace lowlevel {
    /*int            addchstr(const ncCharType* str, int n=-1) {
      return waddchnstr(m_window, str, n); }
    // Write the string str to the window, stop writing if the terminating
    // NUL or the limit n is reached. If n is negative, it is ignored.

    int            addchstr(int y, int x, const ncCharType * str, int n=-1) {
    return mvwaddchnstr(m_window, y, x, str, n); }
    // Move the cursor to the requested position and then perform the addchstr
    // as described above.
    //}*/

    //TODO: This should also be variadic if posible
    /**
     * Do a formatted print to the window.
     */
    int print(const char* fmt, ...)
#if (__GNUG__ >= 2) && !defined(printf)
        __attribute__ ((format (printf, 2, 3)));
#else
    ;
#endif

    /**
     * Move the cursor and then do a formatted print to the window.
     */
    int printAt(int y, int x, const char * fmt, ...)
#if (__GNUG__ >= 2) && !defined(printf)
        __attribute__ ((format (printf, 4, 5)));
#else
    ;
#endif

    /**
     * Retrieve attributed character under the current cursor position.
     *
     * @return the attributed character under the cursor
     */
    NCCharType getCharUnderCursor() const { return winch(m_window); }

    /**
     * Move cursor to requested position and then retrieve attributed character
     * at this position.
     *
     * @param point point to move the cursor to
     * @return the attributed character under the cursor
     */
    NCCharType getCharAtPos(const Point& point) { return mvwinch(m_window, point.y, point.x); }

    //TODO: These are not normal strings but rather ncurses wide character type strings.
    //      These also hold attributes. Consider extractString and similiar and work to ensure
    //      it is udnerstood which one should be used in which circumstances. Additionally,
    //      we cannot simply return a string object.
    /**
     * Read the string str from the window, stop reading if the terminating
     * null or the limit n is reached. If n is negative, it is ignored.
     */
    int getStr(NCCharType* str, int n=-1) {
        return winchnstr(m_window, str, n);
    }

    //TODO: Links
    /**
     * Move the cursor to the requested position and then perform the inchstr
     * as described in getStr.
     */
    int getStrAtPos(Point& pos, NCCharType* str, int n=-1);

    /**
     * Insert attributed character into the window before current cursor position.
     *
     * @param ch the character to insert
     */
    void insertChar(NCCharType ch) { _onError ( winsch(m_window, ch) ); }

    /**
     * Move cursor to requested position and then insert the attributed
     * character before that position.
     *
     * @param point point to move the cursor to
     * @param ch    the character to insert
     */
    int insertCharAtPos(const Point& pos, NCCharType ch) {
        return mvwinsch(m_window, pos.y, pos.x, ch);
    }

    //TODO: Docs
    int insertLine(int n=1) {
        return n > 0 ? winsdelln(m_window, n) : 0;
    }

    //TODO: Docs
    int deleteLine(int n=-1) {
        return n < 0 ? winsdelln(m_window, n) : 0;
    }

    /**
     * Insert the string into the window before the current cursor position.
     *
     * @param str string to insert
     */
    void insertStr(const std::string& str) {
        _onError ( winsnstr(m_window, str.c_str(), str.size()) );
    }

    /**
     * Move the cursor and insert a string.
     *
     * @param pos position to move the cursor to
     * @param str string to insert
     */
    void insertStrAtPos(const Point& pos, const std::string& str) {
        _onError ( mvwinsnstr(m_window, pos.y, pos.x, str.c_str(), str.size() ));
    }

    /**
     * Switch on the window attributes;
     */
    void attributeOn (NCCharType attr) { _onError ( wattron (m_window, attr) ); }

    /**
     * Switch off the window attributes;
     */
    void attributeOff(NCCharType attr) { _onError ( wattroff(m_window, static_cast<int>(attr)) ); }


    // TODO: Make custom type for methods that manipulate attributes
    /**
     * Set the window attributes.
     */
     void setAttribute(NCCharType attr) { _onError ( wattrset(m_window, static_cast<int>(attr)) ); }

    // TODO: Change to struct or other representation
    /**
     * Get the window attributes;
     *
     * @return  //TODO
     */
    NCCharType getAttributes() { return getattrs(m_window); }

    void charAttribute(int n, attr_t attr, ColorPairID color, const void *opts=nullptr) {
        _onError ( wchgat(m_window, n, attr, color, opts) );
    }
    // Change the attributes of the next n characters in the current line. If
    // n is negative or greater than the number of remaining characters in the
    // line, the attributes will be changed up to the end of the line.

    void charAttributeAtPos(Point& pos,
            int n, attr_t attr, ColorPairID color, const void *opts=nullptr) {
        _onError ( mvwchgat(m_window, pos.y, pos.x, n, attr, color, opts) );
    }
    // Move the cursor to the requested position and then perform chgat() as
    // described above.

    NCCharType getBackgroundAttributes() const { return getbkgd(m_window); }
    // Get current background setting.

    /**
     * Set the background property and apply it to the window.
     *
     * @param ch background property
     */
     void setBackgroundAttributes(const NCCharType ch) { _onError ( wbkgd(m_window, ch) ); }

    // TODO: This is for stdcr and should be defined in the globals
    //void bkgdset(ncCharType ch) { wbkgdset(m_window, ch); }
    // Set the background property.

    //TODO Docs and clean up
    /**
     * Draw a border around the window with the given borderType for
     * various parts of the border. If you pass zero for a character, curses
     * will try to find "nice" characters.
     *
     * @param border the border specification to use
     */
    void drawBorder(Border border = {}) {
        _onError ( wborder(m_window,
                border.left,        border.right,
                border.top,         border.bottom,
                border.top_left,    border.top_right,
                border.bottom_left, border.bottom_right
                ));
    }

    /**
     * Draw a horizontal line of len characters with the given character.
     * If you pass zero for the character, curses will try to find a "nice" one.
     *
     * @param len length of the line
     * @param ch  the character that makes up the line
     */
    void horizontalLine(int len, NCCharType ch=0) { _onError ( whline(m_window, ch, len) ); }

    /**
     * Move the cursor to the requested position and then draw a horizontal line.
     *
     * @param point the point to move the cursor to
     * @param len   length of the line
     * @param ch    the character that makes up the line
     */
    void horizontalLineAt(const Point& pos, int len, NCCharType ch=0) {
        _onError ( mvwhline(m_window, pos.y, pos.x, ch, len) );
    }

    /**
     * Draw a vertical line of len characters with the given character.
     * If you pass zero for the character, curses will try to find a "nice" one.
     *
     * @param len length of the line
     * @param ch  the character that makes up the line
     */
    int verticalLine(int len, NCCharType ch=0) { return wvline(m_window, ch, len); }

    /**
     * Move the cursor to the requested position and then draw a vertical line.
     *
     * @param point the point to move the cursor to
     * @param len   length of the line
     * @param ch    the character that makes up the line
     */
    int verticalLineAt(const Point& point, int len, NCCharType ch=0) {
        return mvwvline(m_window, point.y, point.x, ch, len);
    }

    /**
     * Erase the window.
     */
    void erase() { _onError ( werase(m_window) ); }

    /**
     * Clear the window.
     */
    void clear() { _onError ( wclear(m_window) ); }

    /**
     * Set/Reset the clear flag.
     *
     * @param bf If set to true, the next refresh will clear the screen.
     */
    void setClearOkFlag(bool bf) { _onError ( clearok(m_window, bf) ); }

    /**
     * Clear to the end of the window.
     */
    void clearBottom() { _onError ( wclrtobot(m_window) ); }

    /**
     * Clear to the end of the line.
     *
     * Erases the current line to the right of the cursor, inclusive, to
     * the end of the current line.
     */
    void clearToEndOfLine() { _onError ( wclrtoeol(m_window) ); }

    /**
     * Delete character under the cursor.
     */
    void deleteCharUnderCursor() { _onError ( wdelch(m_window) ); }

    /**
     * Move cursor to requested position and delete the character under the cursor.
     */
    void deleteCharAtPos(const Point& pos) { _onError ( mvwdelch(m_window, pos.y, pos.x) ); }

    /**
     * Delete the current line.
     */
    void deleteCurrentLine() { _onError ( winsdelln(m_window, -1) ); }

    /**
     * Scroll an amount lines.
     *
     * If amount is positive, scroll up, otherwise scroll down.
     *
     * @param amount the amount of lines to scroll
     */
    void doScroll(int amount=1) { _onError ( wscrl(m_window, amount) ); }

    /**
     * Set the scrollok flag.
     *
     * If set to true, the window scrolls if cursor is moved off the bottom
     * edge of the window or a scrolling region, otherwise the cursor is left
     * at the bottom line.
     *
     * @param bf value to set the flag to
     */
    void setScrollOkFlag(bool bf) { _onError ( scrollok(m_window, bf) ); }

    /**
     * Define a soft scrolling region.
     *
     * @param from the line number of the top margin
     * @param to   the line number of the bottom margin
     */
    void setSoftScrollingRegion(int from, int to) {
        _onError ( wsetscrreg(m_window, from, to) );
    }

    /**
     * Set the idlok flag.
     *
     * If bf is true, use insert/delete line hardware support if possible.
     * Otherwise do it in software.
     *
     * @param bf value to set the flag to
     */
    void setLineModefyMode(bool bf) { _onError ( idlok(m_window, bf) ); }

    /**
     * Set the idcok flag.
     *
     * If bf is true, use insert/delete character hardware support if possible.
     * Otherwise do it in software.
     *
     * @param bf value to set the flag to
     */
    void setCharacterModifyMode(bool bf) { idcok(m_window, bf); }

    //TODO: this is for standard screen. Have a static function that retunrs a handle
    //      to a Window object of stdscr instead and call it from there
    /**
     * Mark the given lines as modified.
     *
     * @param start the line to start from
     * @param count the number of lines to touch after start
     */
    void touchLine(int start, int count) { _onError ( touchline(m_window, start, count) ); }

    /**
     * Mark the whole window as modified.
     */
    void touch() { _onError ( wtouchln(m_window, 0, height(), 1) ); }

    /**
     * Mark the whole window as unmodified.
     */
    void untouch() { _onError ( wtouchln(m_window, 0, height(), 0) ); }

    /**
     * Mark the given lines as modified.
     *
     * @param start   the line to start from
     * @param count   the number of lines to touch after start
     * @param changed marked as changed if true, otherwise mark as unchanged
     */
    int touchLine(int s, int cnt, bool changed=true) {
        return wtouchln(m_window, s, cnt, static_cast<int>(changed ? 1 : 0));
    }

    /**
     * Check if line is marked as chagned.
     *
     * @return true if line is marked as changed, false otherwise
     */
    bool isLineTouched(int line) const {
        return (is_linetouched(m_window, line) ? true:false);
    }

    /**
     * Checked if the whole window is marked as changed.
     *
     *@return true if window is marked as changed, false otherwise
     */
    bool isTouched() const {
        return (is_wintouched(m_window) ? true:false);
    }

    /**
     * Set leaveok flag.
     *
     * @param bf if true, curses will leave the cursor after an update whereever
     *           it is after the update.
     */
    void setLeaveCursor(bool bf) { _onError ( leaveok(m_window, bf) ); }

    /**
     * Redraw lines.
     *
     * @param from the lien to start from
     * @param n    the number of lines to redraw after start
     */
    int  redrawLines(int from, int n) { return wredrawln(m_window, from, n); }

    /**
     * Redraw the whole window
     */
    void redraw() { _onError ( wredrawln(m_window, 0, height()) ); }

    /**
     * Do all outputs to make the physical screen looking like the virtual one
     */
    void doUpdate()  { _onError ( ::doupdate() ); }

    /**
     * Propagate the changes down to all descendant windows
     */
    void syncDown()  { wsyncdown(m_window); }

    /**
     * Propagate the changes up in the hierarchy
     */
    void syncUp()    { wsyncup(m_window); }

    /**
     * Position the cursor in all ancestor windows corresponding to our setting
     */
    void syncCursorUp() { wcursyncup(m_window); }

    /**
     * Set syncok flag.
     *
     * @param bf if true syncup() is called whenever the window is changed
     */
    void enableSync(bool bf) { _onError ( syncok(m_window, bf) ); }

    /**
     * Set immedok flag.
     *
     * @param bf if true any change in the window will cause an automatic immediate refresh()
     */
    void enableImmediate(bool bf) { immedok(m_window, bf); }

    /**
     * Toggle intrflush.
     *
     * If enabled and an interrupt key is pressed, all output in the tty driver
     * queue will be flushed, giving the effect of faster response to the interrupt.
     * See man curs_inopts(3X).
     *
     * @param bf if true intrflush will be enabled
     */
    void intrFlush(bool bf) { _onError ( intrflush(m_window, bf) ); }

    /**
     * Toggle keypad.
     *
     * If enabled, the user can press a function key and wgetch returns a single value
     * representing the function key.
     * See man curs_inopts(3X)
     *
     * @param bf if true the application will interpret function keys.
     */
    void enableKeypad(bool bf) { _onError ( keypad(m_window, bf) ); }

    /**
     * Toggle nodelay mode.
     *
     * This will cause getch to be a non-blocking call.
     *
     * @param bf if true, enable nodelay mode
     */
    void enableNoDelay(bool bf) { _onError ( nodelay(m_window, bf) ); }

    /**
     * Enforce 7 or 8-bit inputs
     *
     * @param bf If true, keys may generate 8-Bit characters.
     *           Otherwise 7-Bit characters are generated.
     */
    void enableMeta(bool bf) { _onError ( meta(m_window, bf) ); }

    /**
     * Enable "standout" attributes
     */
    void enableStandout() { _onError ( wstandout(m_window) ); }

    /**
     * Disable "standout" attributes
     */
    void disableStandout() { _onError ( wstandend(m_window) ); }

    /**
     * Toggle "standout" attirbues
     *
     * @param bf if true, "standout" attributes will be enabled
     */
    void enableStandout(bool bf) { _onError ( bf ? wstandout(m_window) : wstandend(m_window) ); }

    /**
     * Propagate the changes in this window to the virtual screen and call doupdate().
     */
    virtual void refresh() { _onError ( wrefresh(m_window) ); }

    /**
     * Propagate the changes in this window to the virtual screen.
     */
    virtual void noutrefresh() { _onError ( wnoutrefresh(m_window) ); }

    /**
     * Overlay this window over another window.
     *
     * @param win the window to overlay over
     */
    void overlay(Window& win) {
        _onError ( ::overlay(m_window, win.m_window) );
    }

    /**
     * Overwrite a window with this window.
     *
     * @param win the window to overwrite
     */
    void overwrite(Window& win) {
        _onError ( ::overwrite(m_window, win.m_window) );
    }

    //TODO: Fix this
    /**
     * Overlay or overwrite the rectangle in win given by dminrow,dmincol,
    dmaxrow,dmaxcol with the rectangle in this window beginning at
     sminrow,smincol.
     */
    void copy(Window& win,
            int sminrow, int smincol,
            int dminrow, int dmincol,
            int dmaxrow, int dmaxcol, bool overlaywin=TRUE) {
        _onError (copywin(m_window, win.m_window, sminrow, smincol, dminrow, dmincol,
                dmaxrow, dmaxcol, static_cast<int>(overlaywin ? 1 : 0)) );
    }

    //TODO: Docs
    /**
     * Resize the window.
     *
     * See man wresize(3X)
     *
     * @param size the dimensions to resize the window to
     */
#if defined(NCURSES_EXT_FUNCS) && (NCURSES_EXT_FUNCS != 0)
    void resize(const Size& size) {
        _onError ( wresize(m_window, size.height, size.width) );
    }
#endif

    /**
     * Check if we have a mouse.
     *
     * @return Return true if terminal supports a mouse, false otherwise
     */
    bool hasMouse() const;

    //TODO: Should these be static?
    //int lines() const { return LINES; }
    // Number of lines on terminal, *not* window

    //int cols() const { initialize(); return COLS; }
    // Number of cols  on terminal, *not* window

    //int tabsize() const { initialize(); return TABSIZE; }
    // Size of a tab on terminal, *not* window

    /**
     * Height of this window.
     *
     * @return the number of lines in the curses window
     */
    int height() { return maxY() + 1; }

    /**
     * Width of this window.
     *
     * @return the number of columns in the curses window
     */
    int width() { return maxX() + 1; }

    /**
     * X Coordinate of window origin relative to stdscr
     *
     * @return origin x coordinate
     */
    int originX() const { return getbegx(m_window); }

    /**
     * Y Coordinate of window origin relative to stdscr
     *
     * @return origin y coordinate
     */
    int originY() const { return getbegy(m_window); }

    /**
     * Coordinate pair of the window origin relative to stdscr
     *
     * @return origin coordinate pair
     */
    Point origin() const {
        Point point {};
        getbegyx(m_window, point.y, point.x);
        return point;
    }

    /**
     * X Coordinate of cursor position relative to stdscr
     *
     * @return cursor x coordinate
     */
    int cursorX() const { return getcurx(m_window); }

    /**
     * Y Coordinate of cursor position relative to stdscr
     *
     * @return cursor y coordinate
     */
    int cursorY() const { return getcury(m_window); }

    /**
     * Coordinate pair of cursor position relative to stdscr
     *
     * @return cursor coordinate pair
     */
    Point cursorPos() const {
        Point point {};
        getyx(m_window, point.y, point.x);
        return point;
    }

    /**
     * Largest x coordinate in window
     *
     * @return window max x coordinate
     */
    int maxX() {
        if (getmaxx(m_window) == ERR) {
            _onError(ERR);
            return 0;
        }
        return getmaxx(m_window)-1;
    }

    /**
     * Largest y coordinate in window
     *
     * @return window max y coordinate
     */
    int maxY() {
        if (getmaxy(m_window) == ERR) {
            _onError(ERR);
            return 0;
        }
        return getmaxy(m_window)-1;
    }

    /**
     * Check if we are a descendant of the given window.
     *
     * @param win window to check inherantace
     *
     * @return true if the window is a descendant of win
     *         false otherwise
     */
    bool isDescendant(Window& win);

    /**
     * Get parent's origin of the window
     *
     * @return coordinate pair of parent's origin
     */
    Point getParentPoint() const {
        int x = 0;
        int y = 0;
        getparyx(m_window, y, x);
        return Point{x, y};
    }

    /**
     * Get the first child window
     *
     * @return pointer to child window
     */
    Window*  child() { return m_subWins; }

    /**
     * Get the next child from the parent.
     *
     * @return ponter to the sibling of the parent
     */
    Window*  sibling() { return m_sib; }

    /**
     * Get this window's parent
     *
     * @return pointer to the window's parent
     */
    Window*  parent() { return m_parent; }

    /**
     * Get the NCurses WINDOW* handle.
     *
     * This is should be used with care.
     */
    WINDOW* getHandle() const
    {
        return m_window;
    }

    protected:

    /**
     * NCurses WINDOW handle
     */
    WINDOW* m_window = nullptr;

    /**
     * Reference to a parent window.
     *
     * This wiil be null if this window is not a subwindow.
     */
    Window* m_parent = nullptr;

    //TODO: This is a linked list and should be reflect as such in code.
    //      Consider a modern C++ alternative
    /**
     * Head of subwindows list
     */
    Window* m_subWins = nullptr;

    /**
     * Next subwindow of the parent
     */
    Window* m_sib = nullptr;   // next subWindow of parent

    private:

    //TODO: Docs
    void _killSubwindows();
    static void setPalette(const ColorPair& color, ColorPairID pair);
    short getPair() const;
    static void _onError(int err);

    ColorType getColor(int getBack) const;
    static bool s_isInitialized;

    bool m_isHandleOwner = true;
};

} // namespace ncurses
} // namespace ncf

#endif
