#ifndef NCURSES_WINDOW_BINDINGS_H_
#define NCURSES_WINDOW_BINDINGS_H_

extern "C" {
#include <curses.h>
#include <panel.h>
}

#include <functional>
#include <memory>
#include <iostream>

/* SCO 3.2v4 curses.h includes term.h, which defines lines as a macro.
   Undefine it here, because NCursesWindow uses lines as a method.  */
#undef lines

/* "Convert" macros to inlines. We'll define it as another symbol to avoid
 * conflict with library symbols.
 */
#undef UNDEF
#define UNDEF(name) CUR_ ##name

#ifdef addch
inline int UNDEF(addch)(chtype ch)  { return addch(ch); }
#undef addch
#define addch UNDEF(addch)
#endif

#ifdef addchstr
inline int UNDEF(addchstr)(chtype *at) { return addchstr(at); }
#undef addchstr
#define addchstr UNDEF(addchstr)
#endif

#ifdef addnstr
inline int UNDEF(addnstr)(const char *str, int n)
{ return addnstr(str, n); }
#undef addnstr
#define addnstr UNDEF(addnstr)
#endif

#ifdef addstr
inline int UNDEF(addstr)(const char * str)  { return addstr(str); }
#undef addstr
#define addstr UNDEF(addstr)
#endif

#ifdef attroff
inline int UNDEF(attroff)(chtype at) { return attroff(at); }
#undef attroff
#define attroff UNDEF(attroff)
#endif

#ifdef attron
inline int UNDEF(attron)(chtype at) { return attron(at); }
#undef attron
#define attron UNDEF(attron)
#endif

#ifdef attrset
inline chtype UNDEF(attrset)(chtype at) { return attrset(at); }
#undef attrset
#define attrset UNDEF(attrset)
#endif

#ifdef bkgd
inline int UNDEF(bkgd)(chtype ch) { return bkgd(ch); }
#undef bkgd
#define bkgd UNDEF(bkgd)
#endif

#ifdef bkgdset
inline void UNDEF(bkgdset)(chtype ch) { bkgdset(ch); }
#undef bkgdset
#define bkgdset UNDEF(bkgdset)
#endif

#ifdef border
inline int UNDEF(border)(chtype ls, chtype rs, chtype ts, chtype bs, chtype tl, chtype tr, chtype bl, chtype br)
{ return border(ls, rs, ts, bs, tl, tr, bl, br); }
#undef border
#define border UNDEF(border)
#endif

#ifdef box
inline int UNDEF(box)(WINDOW *win, int v, int h) { return box(win, v, h); }
#undef box
#define box UNDEF(box)
#endif

#ifdef chgat
inline int UNDEF(chgat)(int n, attr_t attr, NCURSES_PAIRS_T color, const void *opts) {
  return chgat(n, attr, color, opts); }
#undef chgat
#define chgat UNDEF(chgat)
#endif

#ifdef clear
inline int UNDEF(clear)()  { return clear(); }
#undef clear
#define clear UNDEF(clear)
#endif

#ifdef clearok
inline int UNDEF(clearok)(WINDOW* win, bool bf)  { return clearok(win, bf); }
#undef clearok
#define clearok UNDEF(clearok)
#else
extern "C" NCURSES_IMPEXP int NCURSES_API clearok(WINDOW*, bool);
#endif

#ifdef clrtobot
inline int UNDEF(clrtobot)()  { return clrtobot(); }
#undef clrtobot
#define clrtobot UNDEF(clrtobot)
#endif

#ifdef clrtoeol
inline int UNDEF(clrtoeol)()  { return clrtoeol(); }
#undef clrtoeol
#define clrtoeol UNDEF(clrtoeol)
#endif

#ifdef color_set
inline chtype UNDEF(color_set)(NCURSES_PAIRS_T p, void* opts) { return color_set(p, opts); }
#undef color_set
#define color_set UNDEF(color_set)
#endif

#ifdef crmode
inline int UNDEF(crmode)(void) { return crmode(); }
#undef crmode
#define crmode UNDEF(crmode)
#endif

#ifdef delch
inline int UNDEF(delch)()  { return delch(); }
#undef delch
#define delch UNDEF(delch)
#endif

#ifdef deleteln
inline int UNDEF(deleteln)()  { return deleteln(); }
#undef deleteln
#define deleteln UNDEF(deleteln)
#endif

#ifdef echochar
inline int UNDEF(echochar)(chtype ch)  { return echochar(ch); }
#undef echochar
#define echochar UNDEF(echochar)
#endif

#ifdef erase
inline int UNDEF(erase)()  { return erase(); }
#undef erase
#define erase UNDEF(erase)
#endif

#ifdef fixterm
inline int UNDEF(fixterm)(void) { return fixterm(); }
#undef fixterm
#define fixterm UNDEF(fixterm)
#endif

#ifdef flushok
inline int UNDEF(flushok)(WINDOW* _win, bool _bf)  {
  return flushok(_win, _bf); }
#undef flushok
#define flushok UNDEF(flushok)
#else
#define _no_flushok
#endif

#ifdef getattrs
inline int UNDEF(getattrs)(WINDOW *win) { return getattrs(win); }
#undef getattrs
#define getattrs UNDEF(getattrs)
#endif

#ifdef getbegyx
inline void UNDEF(getbegyx)(WINDOW* win, int& y, int& x) { getbegyx(win, y, x); }
#undef getbegyx
#define getbegyx UNDEF(getbegyx)
#endif

#ifdef getbkgd
inline chtype UNDEF(getbkgd)(const WINDOW *win) { return getbkgd(win); }
#undef getbkgd
#define getbkgd UNDEF(getbkgd)
#endif

#ifdef getch
inline int UNDEF(getch)()  { return getch(); }
#undef getch
#define getch UNDEF(getch)
#endif

#ifdef getmaxyx
inline void UNDEF(getmaxyx)(WINDOW* win, int& y, int& x) { getmaxyx(win, y, x); }
#undef getmaxyx
#define getmaxyx UNDEF(getmaxyx)
#endif

#ifdef getnstr
inline int UNDEF(getnstr)(char *_str, int n)  { return getnstr(_str, n); }
#undef getnstr
#define getnstr UNDEF(getnstr)
#endif

#ifdef getparyx
inline void UNDEF(getparyx)(WINDOW* win, int& y, int& x) { getparyx(win, y, x); }
#undef getparyx
#define getparyx UNDEF(getparyx)
#endif

#ifdef getstr
inline int UNDEF(getstr)(char *_str)  { return getstr(_str); }
#undef getstr
#define getstr UNDEF(getstr)
#endif

#ifdef getyx
inline void UNDEF(getyx)(const WINDOW* win, int& y, int& x) {
  getyx(win, y, x); }
#undef getyx
#define getyx UNDEF(getyx)
#endif

#ifdef hline
inline int UNDEF(hline)(chtype ch, int n) { return hline(ch, n); }
#undef hline
#define hline UNDEF(hline)
#endif

#ifdef inch
inline chtype UNDEF(inch)()  { return inch(); }
#undef inch
#define inch UNDEF(inch)
#endif

#ifdef inchstr
inline int UNDEF(inchstr)(chtype *str)  { return inchstr(str); }
#undef inchstr
#define inchstr UNDEF(inchstr)
#endif

#ifdef innstr
inline int UNDEF(innstr)(char *_str, int n)  { return innstr(_str, n); }
#undef innstr
#define innstr UNDEF(innstr)
#endif

#ifdef insch
inline int UNDEF(insch)(chtype c)  { return insch(c); }
#undef insch
#define insch UNDEF(insch)
#endif

#ifdef insdelln
inline int UNDEF(insdelln)(int n)  { return insdelln(n); }
#undef insdelln
#define insdelln UNDEF(insdelln)
#endif

#ifdef insertln
inline int UNDEF(insertln)()  { return insertln(); }
#undef insertln
#define insertln UNDEF(insertln)
#endif

#ifdef insnstr
inline int UNDEF(insnstr)(const char *_str, int n)  {
  return insnstr(_str, n); }
#undef insnstr
#define insnstr UNDEF(insnstr)
#endif

#ifdef insstr
inline int UNDEF(insstr)(const char *_str)  {
  return insstr(_str); }
#undef insstr
#define insstr UNDEF(insstr)
#endif

#ifdef instr
inline int UNDEF(instr)(char *_str)  { return instr(_str); }
#undef instr
#define instr UNDEF(instr)
#endif

#ifdef intrflush
inline void UNDEF(intrflush)(WINDOW *win, bool bf) { intrflush(); }
#undef intrflush
#define intrflush UNDEF(intrflush)
#endif

#ifdef leaveok
inline int UNDEF(leaveok)(WINDOW* win, bool bf)  { return leaveok(win, bf); }
#undef leaveok
#define leaveok UNDEF(leaveok)
#else
extern "C" NCURSES_IMPEXP int NCURSES_API leaveok(WINDOW* win, bool bf);
#endif

#ifdef move
inline int UNDEF(move)(int x, int y)  { return move(x, y); }
#undef move
#define move UNDEF(move)
#endif

#ifdef mvaddch
inline int UNDEF(mvaddch)(int y, int x, chtype ch)
{ return mvaddch(y, x, ch); }
#undef mvaddch
#define mvaddch UNDEF(mvaddch)
#endif

#ifdef mvaddnstr
inline int UNDEF(mvaddnstr)(int y, int x, const char *str, int n)
{ return mvaddnstr(y, x, str, n); }
#undef mvaddnstr
#define mvaddnstr UNDEF(mvaddnstr)
#endif

#ifdef mvaddstr
inline int UNDEF(mvaddstr)(int y, int x, const char * str)
{ return mvaddstr(y, x, str); }
#undef mvaddstr
#define mvaddstr UNDEF(mvaddstr)
#endif

#ifdef mvchgat
inline int UNDEF(mvchgat)(int y, int x, int n,
			  attr_t attr, NCURSES_PAIRS_T color, const void *opts) {
  return mvchgat(y, x, n, attr, color, opts); }
#undef mvchgat
#define mvchgat UNDEF(mvchgat)
#endif

#ifdef mvdelch
inline int UNDEF(mvdelch)(int y, int x) { return mvdelch(y, x);}
#undef mvdelch
#define mvdelch UNDEF(mvdelch)
#endif

#ifdef mvgetch
inline int UNDEF(mvgetch)(int y, int x) { return mvgetch(y, x);}
#undef mvgetch
#define mvgetch UNDEF(mvgetch)
#endif

#ifdef mvgetnstr
inline int UNDEF(mvgetnstr)(int y, int x, char *str, int n) {
  return mvgetnstr(y, x, str, n);}
#undef mvgetnstr
#define mvgetnstr UNDEF(mvgetnstr)
#endif

#ifdef mvgetstr
inline int UNDEF(mvgetstr)(int y, int x, char *str) {return mvgetstr(y, x, str);}
#undef mvgetstr
#define mvgetstr UNDEF(mvgetstr)
#endif

#ifdef mvinch
inline chtype UNDEF(mvinch)(int y, int x) { return mvinch(y, x);}
#undef mvinch
#define mvinch UNDEF(mvinch)
#endif

#ifdef mvinnstr
inline int UNDEF(mvinnstr)(int y, int x, char *_str, int n) {
  return mvinnstr(y, x, _str, n); }
#undef mvinnstr
#define mvinnstr UNDEF(mvinnstr)
#endif

#ifdef mvinsch
inline int UNDEF(mvinsch)(int y, int x, chtype c)
{ return mvinsch(y, x, c); }
#undef mvinsch
#define mvinsch UNDEF(mvinsch)
#endif

#ifdef mvinsnstr
inline int UNDEF(mvinsnstr)(int y, int x, const char *_str, int n) {
  return mvinsnstr(y, x, _str, n); }
#undef mvinsnstr
#define mvinsnstr UNDEF(mvinsnstr)
#endif

#ifdef mvinsstr
inline int UNDEF(mvinsstr)(int y, int x, const char *_str)  {
  return mvinsstr(y, x, _str); }
#undef mvinsstr
#define mvinsstr UNDEF(mvinsstr)
#endif

#ifdef mvwaddch
inline int UNDEF(mvwaddch)(WINDOW *win, int y, int x, const chtype ch)
{ return mvwaddch(win, y, x, ch); }
#undef mvwaddch
#define mvwaddch UNDEF(mvwaddch)
#endif

#ifdef mvwaddchnstr
inline int UNDEF(mvwaddchnstr)(WINDOW *win, int y, int x, const chtype *str, int n)
{ return mvwaddchnstr(win, y, x, str, n); }
#undef mvwaddchnstr
#define mvwaddchnstr UNDEF(mvwaddchnstr)
#endif

#ifdef mvwaddchstr
inline int UNDEF(mvwaddchstr)(WINDOW *win, int y, int x, const chtype *str)
{ return mvwaddchstr(win, y, x, str); }
#undef mvwaddchstr
#define mvwaddchstr UNDEF(mvwaddchstr)
#endif

#ifdef mvwaddnstr
inline int UNDEF(mvwaddnstr)(WINDOW *win, int y, int x, const char *str, int n)
{ return mvwaddnstr(win, y, x, str, n); }
#undef mvwaddnstr
#define mvwaddnstr UNDEF(mvwaddnstr)
#endif

#ifdef mvwaddstr
inline int UNDEF(mvwaddstr)(WINDOW *win, int y, int x, const char * str)
{ return mvwaddstr(win, y, x, str); }
#undef mvwaddstr
#define mvwaddstr UNDEF(mvwaddstr)
#endif

#ifdef mvwchgat
inline int UNDEF(mvwchgat)(WINDOW *win, int y, int x, int n,
			   attr_t attr, NCURSES_PAIRS_T color, const void *opts) {
  return mvwchgat(win, y, x, n, attr, color, opts); }
#undef mvwchgat
#define mvwchgat UNDEF(mvwchgat)
#endif

#ifdef mvwdelch
inline int UNDEF(mvwdelch)(WINDOW *win, int y, int x)
{ return mvwdelch(win, y, x); }
#undef mvwdelch
#define mvwdelch UNDEF(mvwdelch)
#endif

#ifdef mvwgetch
inline int UNDEF(mvwgetch)(WINDOW *win, int y, int x) { return mvwgetch(win, y, x);}
#undef mvwgetch
#define mvwgetch UNDEF(mvwgetch)
#endif

#ifdef mvwgetnstr
inline int UNDEF(mvwgetnstr)(WINDOW *win, int y, int x, char *str, int n)
{return mvwgetnstr(win, y, x, str, n);}
#undef mvwgetnstr
#define mvwgetnstr UNDEF(mvwgetnstr)
#endif

#ifdef mvwgetstr
inline int UNDEF(mvwgetstr)(WINDOW *win, int y, int x, char *str)
{return mvwgetstr(win, y, x, str);}
#undef mvwgetstr
#define mvwgetstr UNDEF(mvwgetstr)
#endif

#ifdef mvwhline
inline int UNDEF(mvwhline)(WINDOW *win, int y, int x, chtype c, int n) {
  return mvwhline(win, y, x, c, n); }
#undef mvwhline
#define mvwhline UNDEF(mvwhline)
#endif

#ifdef mvwinch
inline chtype UNDEF(mvwinch)(WINDOW *win, int y, int x) {
  return mvwinch(win, y, x);}
#undef mvwinch
#define mvwinch UNDEF(mvwinch)
#endif

#ifdef mvwinchnstr
inline int UNDEF(mvwinchnstr)(WINDOW *win, int y, int x, chtype *str, int n)  { return mvwinchnstr(win, y, x, str, n); }
#undef mvwinchnstr
#define mvwinchnstr UNDEF(mvwinchnstr)
#endif

#ifdef mvwinchstr
inline int UNDEF(mvwinchstr)(WINDOW *win, int y, int x, chtype *str)  { return mvwinchstr(win, y, x, str); }
#undef mvwinchstr
#define mvwinchstr UNDEF(mvwinchstr)
#endif

#ifdef mvwinnstr
inline int UNDEF(mvwinnstr)(WINDOW *win, int y, int x, char *_str, int n) {
  return mvwinnstr(win, y, x, _str, n); }
#undef mvwinnstr
#define mvwinnstr UNDEF(mvwinnstr)
#endif

#ifdef mvwinsch
inline int UNDEF(mvwinsch)(WINDOW *win, int y, int x, chtype c)
{ return mvwinsch(win, y, x, c); }
#undef mvwinsch
#define mvwinsch UNDEF(mvwinsch)
#endif

#ifdef mvwinsnstr
inline int UNDEF(mvwinsnstr)(WINDOW *w, int y, int x, const char *_str, int n) {
  return mvwinsnstr(w, y, x, _str, n); }
#undef mvwinsnstr
#define mvwinsnstr UNDEF(mvwinsnstr)
#endif

#ifdef mvwinsstr
inline int UNDEF(mvwinsstr)(WINDOW *w, int y, int x,  const char *_str)  {
  return mvwinsstr(w, y, x, _str); }
#undef mvwinsstr
#define mvwinsstr UNDEF(mvwinsstr)
#endif

#ifdef mvwvline
inline int UNDEF(mvwvline)(WINDOW *win, int y, int x, chtype c, int n) {
  return mvwvline(win, y, x, c, n); }
#undef mvwvline
#define mvwvline UNDEF(mvwvline)
#endif

#ifdef napms
inline void UNDEF(napms)(unsigned long x) { napms(x); }
#undef napms
#define napms UNDEF(napms)
#endif

#ifdef nocrmode
inline int UNDEF(nocrmode)(void) { return nocrmode(); }
#undef nocrmode
#define nocrmode UNDEF(nocrmode)
#endif

#ifdef nodelay
inline void UNDEF(nodelay)() { nodelay(); }
#undef nodelay
#define nodelay UNDEF(nodelay)
#endif

#ifdef redrawwin
inline int UNDEF(redrawwin)(WINDOW *win)  { return redrawwin(win); }
#undef redrawwin
#define redrawwin UNDEF(redrawwin)
#endif

#ifdef refresh
inline int UNDEF(refresh)()  { return refresh(); }
#undef refresh
#define refresh UNDEF(refresh)
#endif

#ifdef resetterm
inline int UNDEF(resetterm)(void) { return resetterm(); }
#undef resetterm
#define resetterm UNDEF(resetterm)
#endif

#ifdef saveterm
inline int UNDEF(saveterm)(void) { return saveterm(); }
#undef saveterm
#define saveterm UNDEF(saveterm)
#endif

#ifdef scrl
inline int UNDEF(scrl)(int l) { return scrl(l); }
#undef scrl
#define scrl UNDEF(scrl)
#endif

#ifdef scroll
inline int UNDEF(scroll)(WINDOW *win) { return scroll(win); }
#undef scroll
#define scroll UNDEF(scroll)
#endif

#ifdef scrollok
inline int UNDEF(scrollok)(WINDOW* win, bool bf)  { return scrollok(win, bf); }
#undef scrollok
#define scrollok UNDEF(scrollok)
#else
#if	defined(__NCURSES_H)
extern "C" NCURSES_IMPEXP int NCURSES_API scrollok(WINDOW*, bool);
#else
extern "C" NCURSES_IMPEXP int NCURSES_API scrollok(WINDOW*, char);
#endif
#endif

#ifdef setscrreg
inline int UNDEF(setscrreg)(int t, int b) { return setscrreg(t, b); }
#undef setscrreg
#define setscrreg UNDEF(setscrreg)
#endif

#ifdef standend
inline int UNDEF(standend)()  { return standend(); }
#undef standend
#define standend UNDEF(standend)
#endif

#ifdef standout
inline int UNDEF(standout)()  { return standout(); }
#undef standout
#define standout UNDEF(standout)
#endif

#ifdef subpad
inline WINDOW *UNDEF(subpad)(WINDOW *p, int l, int c, int y, int x)
{ return derwin(p, l, c, y, x); }
#undef subpad
#define subpad UNDEF(subpad)
#endif

#ifdef timeout
inline void UNDEF(timeout)(int delay) { timeout(delay); }
#undef timeout
#define timeout UNDEF(timeout)
#endif

#ifdef touchline
inline int UNDEF(touchline)(WINDOW *win, int s, int c)
{ return touchline(win, s, c); }
#undef touchline
#define touchline UNDEF(touchline)
#endif

#ifdef touchwin
inline int UNDEF(touchwin)(WINDOW *win) { return touchwin(win); }
#undef touchwin
#define touchwin UNDEF(touchwin)
#endif

#ifdef untouchwin
inline int UNDEF(untouchwin)(WINDOW *win) { return untouchwin(win); }
#undef untouchwin
#define untouchwin UNDEF(untouchwin)
#endif

#ifdef vline
inline int UNDEF(vline)(chtype ch, int n) { return vline(ch, n); }
#undef vline
#define vline UNDEF(vline)
#endif

#ifdef waddchstr
inline int UNDEF(waddchstr)(WINDOW *win, chtype *at) { return waddchstr(win, at); }
#undef waddchstr
#define waddchstr UNDEF(waddchstr)
#endif

#ifdef waddstr
inline int UNDEF(waddstr)(WINDOW *win, char *str) { return waddstr(win, str); }
#undef waddstr
#define waddstr UNDEF(waddstr)
#endif

#ifdef wattroff
inline int UNDEF(wattroff)(WINDOW *win, int att) { return wattroff(win, att); }
#undef wattroff
#define wattroff UNDEF(wattroff)
#endif

#ifdef wattrset
inline int UNDEF(wattrset)(WINDOW *win, int att) { return wattrset(win, att); }
#undef wattrset
#define wattrset UNDEF(wattrset)
#endif

#ifdef winch
inline chtype UNDEF(winch)(const WINDOW* win) { return winch(win); }
#undef winch
#define winch UNDEF(winch)
#endif

#ifdef winchnstr
inline int UNDEF(winchnstr)(WINDOW *win, chtype *str, int n)  { return winchnstr(win, str, n); }
#undef winchnstr
#define winchnstr UNDEF(winchnstr)
#endif

#ifdef winchstr
inline int UNDEF(winchstr)(WINDOW *win, chtype *str)  { return winchstr(win, str); }
#undef winchstr
#define winchstr UNDEF(winchstr)
#endif

#ifdef winsstr
inline int UNDEF(winsstr)(WINDOW *w, const char *_str)  {
  return winsstr(w, _str); }
#undef winsstr
#define winsstr UNDEF(winsstr)
#endif

#ifdef wstandend
inline int UNDEF(wstandend)(WINDOW *win)  { return wstandend(win); }
#undef wstandend
#define wstandend UNDEF(wstandend)
#endif

#ifdef wstandout
inline int UNDEF(wstandout)(WINDOW *win)  { return wstandout(win); }
#undef wstandout
#define wstandout UNDEF(wstandout)
#endif


class Window;

//TODO: make attribute a struct/class to use RAII to reset attron/attroff
//TODO: implement interface for all window functionality that needs to be
//      exposed in Window class
//
//TODO: Make int y, int x pairs to Point structs
//TODO: Complete panel implementation

struct Point {
    int x;
    int y;
};

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

        static int     NumberOfColors();
        // Number of available colors

        /**
         * Returns the number of available for this window
         * @return the number of colors
         */
        int Colors() const { return NumberOfColors(); }

        // -------------------------------------------------------------------------
        // window status
        // -------------------------------------------------------------------------

        int GetCursorX() const { return getcurx(m_handle); }
        // Column of top left corner relative to stdscr

        int GetCursorY() const { return getcury(m_handle); }
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
        int MoveCursor(int y, int x) { return ::wmove(m_handle, y, x); }
        // Move cursor the this position. Only moves cursor on virtual screen and
        // needs refresh to update position in physical screen

        Point GetCursorPosition() const;
        // Get current position of the cursor

        Point GetOriginPoint() const;
        // Get beginning of the window

        int Size() const;
        // Get size of the window

        int MoveCursorImmediately(int oldrow, int oldcol, int newrow, int newcol) const {
            return ::mvcur(oldrow, oldcol, newrow, newcol); }
        // Perform lowlevel cursor motion that takes effect immediately.

        // -------------------------------------------------------------------------
        // input
        // -------------------------------------------------------------------------
        //TODO: Return of GetKeyStroke should probably have alias/user type
        int GetKeystroke() { return ::wgetch(m_handle); }
        // Get a keystroke from the window.

        int  GetKeyStrokeFromPos(int y, int x) { return mvwgetch(m_handle, y, x); }
        // Move cursor to position and get a keystroke from the window

        int  Getline(std::string& str, int n=-1);
        // Read a series of characters into str until a newline or carriage return
        // is received. Read at most n characters. If n is negative, the limit is
        // ignored.

        int GetlineFromPos(int y, int x, std::string& str, int n=-1);
        // Move the cursor to the requested position and then perform the getstr()
        // as described above.

        int ExtractString(std::string& str, int n=-1);
        // Get a string of characters from the window into the buffer s. Retrieve
        // at most n characters, if n is negative retrieve all characters up to the
        // end of the current line. Attributes are stripped from the characters.

        int ExtractStringFromPos(int y, int x, std::string& s, int n=-1);
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
        int PutChr(const chtype ch) { return ::waddch(m_handle, ch); }
        // Put attributed character to the window.

        int PutChrAtPos(int y, int x, const chtype ch) {
            return mvwaddch(m_handle, y, x, ch); }
        // Move cursor to the requested position and then put attributed character
        // to the window.

        virtual int EchoChar(const chtype ch) { return ::wechochar(m_handle, ch); }
        // Put attributed character to the window and refresh it immediately.

        int WriteString(const std::string& str, int n=-1) {
            return ::waddnstr(m_handle, str.c_str(), n);
        }
        // Write the string str to the window, stop writing if the terminating
        // NUL or the limit n is reached. If n is negative, it is ignored.

        int WriteStringAtPos(int y, int x, const std::string& str, int n=-1) {
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

        int Print(const char* fmt, ...)
            // Do a formatted print to the window.
#if (__GNUG__ >= 2) && !defined(printf)
            __attribute__ ((format (printf, 2, 3)));
#else
        ;
#endif

        int PrintAt(int y, int x, const char * fmt, ...)
            // Move the cursor and then do a formatted print to the window.
#if (__GNUG__ >= 2) && !defined(printf)
            __attribute__ ((format (printf, 4, 5)));
#else
        ;
#endif

        chtype GetChrOnCursor() const { return ::winch(m_handle); }
        // Retrieve attributed character under the current cursor position.

        chtype GetChrAtPos(int y, int x) { return mvwinch(m_handle, y, x); }
        // Move cursor to requested position and then retrieve attributed character
        // at this position.

        int GetStr(chtype* str, int n=-1) {
            return ::winchnstr(m_handle, str, n);
        }
        // Read the string str from the window, stop reading if the terminating
        // NUL or the limit n is reached. If n is negative, it is ignored.

        int GetStrAtPos(int y, int x, chtype* str, int n=-1);
        // Move the cursor to the requested position and then perform the inchstr
        // as described above.

        int InsertChar(chtype ch) { return ::winsch(m_handle, ch); }
        // Insert attributed character into the window before current cursor
        // position.

        int InsertCharAtPos(int y, int x, chtype ch) {
            return mvwinsch(m_handle, y, x, ch);
        }
        // Move cursor to requested position and then insert the attributed
        // character before that position.

        int InsertLine(int n=1) {
            return n > 0 ? ::winsdelln(m_handle, n) : 0;
        }

        int DeleteLine(int n=-1) {
            return n < 0 ? ::winsdelln(m_handle, n) : 0;
        }

        int InsertStr(const char *s, int n=-1) {
            return ::winsnstr(m_handle, s, n); }
        // Insert the string into the window before the current cursor position.
        // Insert stops at end of string or when the limit n is reached. If n is
        // negative, it is ignored.

        int InsertStrAtPos(int y, int x, const char *s, int n=-1) {
            return mvwinsnstr(m_handle, y, x, s, n); }
        // Move the cursor to the requested position and then perform the insstr()
        // as described above.

        // TODO: Make custom type for methods that manipulate attributes
        int SetAttribute(chtype at) { return wattrset(m_handle, static_cast<int>(at)); }
        // Set the window attributes;

        chtype GetAttributes() { return getattrs(m_handle); }
        // Get the window attributes;
        // TODO: Change to struct or other representation

        int SetColor(NCURSES_PAIRS_T color_pair_number, void* opts=NULL) {
            return ::wcolor_set(m_handle, color_pair_number, opts); }
        // Set the window color attribute;

        int CharAttribute(int n, attr_t attr, NCURSES_PAIRS_T color, const void *opts=NULL) {
            return ::wchgat(m_handle, n, attr, color, opts); }
        // Change the attributes of the next n characters in the current line. If
        // n is negative or greater than the number of remaining characters in the
        // line, the attributes will be changed up to the end of the line.

        int CharAttributeAtPos(int y, int x,
                int n, attr_t attr, NCURSES_PAIRS_T color, const void *opts=NULL) {
            return mvwchgat(m_handle, y, x, n, attr, color, opts); }
        // Move the cursor to the requested position and then perform chgat() as
        // described above.

        // -------------------------------------------------------------------------
        // background
        // -------------------------------------------------------------------------
        chtype GetBackgroundAttributes() const { return getbkgd(m_handle); }
        // Get current background setting.

        int    SetBackgroundAttributes(const chtype ch) { return wbkgd(m_handle, ch); }
        // Set the background property and apply it to the window.

        // TODO: This is for stdcr and should be defined in the globals
        //void bkgdset(chtype ch) { ::wbkgdset(m_handle, ch); }
        // Set the background property.

        // -------------------------------------------------------------------------
        // borders
        // -------------------------------------------------------------------------
        int Box(chtype vert=0, chtype  hor=0) {
            return ::wborder(m_handle, vert, vert, hor, hor, 0, 0, 0, 0); }
        // Draw a box around the window with the given vertical and horizontal
        // drawing characters. If you specify a zero as character, curses will try
        // to find a "nice" character.

        int Border(chtype left=0, chtype right=0,
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
        int HorizontalLine(int len, chtype ch=0) { return ::whline(m_handle, ch, len); }
        // Draw a horizontal line of len characters with the given character. If
        // you pass zero for the character, curses will try to find a "nice" one.

        int HorizontalLineAt(int y, int x, int len, chtype ch=0) {
            return mvwhline(m_handle, y, x, ch, len); }
        // Move the cursor to the requested position and then draw a horizontal line.

        int VerticalLine(int len, chtype ch=0) { return ::wvline(m_handle, ch, len); }
        // Draw a vertical line of len characters with the given character. If
        // you pass zero for the character, curses will try to find a "nice" one.

        int VerticalLineAt(int y, int x, int len, chtype ch=0) {
            return mvwvline(m_handle, y, x, ch, len); }
        // Move the cursor to the requested position and then draw a vertical line.

        // -------------------------------------------------------------------------
        // erasure
        // -------------------------------------------------------------------------
        int Erase() { return ::werase(m_handle); }
        // Erase the window.

        int Clear() { return ::wclear(m_handle); }
        // Clear the window.

        int SetClearOkFlag(bool bf) { return ::clearok(m_handle, bf); }
        // Set/Reset the clear flag. If set, the next refresh() will clear the
        // screen.

        int ClearBottom() { return ::wclrtobot(m_handle); }
        // Clear to the end of the window.

        int ClearToEndOfLine() { return ::wclrtoeol(m_handle); }
        // Clear to the end of the line.

        int DeleteCharUnderCursor() { return ::wdelch(m_handle); }
        // Delete character under the cursor.

        int DeleteCharAtPos(int y, int x) { return mvwdelch(m_handle, y, x); }
        // Move cursor to requested position and delete the character under the
        // cursor.

        int DeleteCurrentLine() { return ::winsdelln(m_handle, -1); }
        // Delete the current line.

        // -------------------------------------------------------------------------
        // screen control
        // -------------------------------------------------------------------------
        int Scroll(int amount=1) { return ::wscrl(m_handle, amount); }
        // Scroll amount lines. If amount is positive, scroll up, otherwise
        // scroll down.

        int  SetScrollOkFlag(bool bf) { return ::scrollok(m_handle, bf); }
        // If bf is TRUE, window scrolls if cursor is moved off the bottom
        // edge of the window or a scrolling region, otherwise the cursor is left
        // at the bottom line.

        int SetSoftScrollingRegion(int from, int to) {
            return ::wsetscrreg(m_handle, from, to); }
        // Define a soft scrolling region.

        int SetLineModefyMode(bool bf) { return ::idlok(m_handle, bf); }
        // If bf is TRUE, use insert/delete line hardware support if possible.
        // Otherwise do it in software.

        void SetCharacterModifyMode(bool bf) { ::idcok(m_handle, bf); }
        // If bf is TRUE, use insert/delete character hardware support if possible.
        // Otherwise do it in software.

        int  TouchLine(int s, int c) { return ::touchline(m_handle, s, c); }
        // Mark the given lines as modified.

        int Touch()   { return ::wtouchln(m_handle, 0, Height(), 1); }
        // Mark the whole window as modified.

        int Untouch() { return ::wtouchln(m_handle, 0, Height(), 0); }
        // Mark the whole window as unmodified.

        int TouchLine(int s, int cnt, bool changed=TRUE) {
            return ::wtouchln(m_handle, s, cnt, static_cast<int>(changed ? 1 : 0)); }
        // Mark cnt lines beginning from line s as changed or unchanged, depending
        // on the value of the changed flag.

        bool IsLineTouched(int line) const {
            return (::is_linetouched(m_handle, line) ? TRUE:FALSE); }
        // Return TRUE if line is marked as changed, FALSE otherwise

        bool IsTouched() const {
            return (::is_wintouched(m_handle) ? TRUE:FALSE); }
        // Return TRUE if window is marked as changed, FALSE otherwise

        int SetLeaveCursor(bool bf) { return ::leaveok(m_handle, bf); }
        // If bf is TRUE, curses will leave the cursor after an update whereever
        // it is after the update.

        int  RedrawLines(int from, int n) { return ::wredrawln(m_handle, from, n); }
        // Redraw n lines starting from the requested line

        int  Redraw() { return ::wredrawln(m_handle, 0, Height()); }
        // Redraw the whole window

        int            doupdate()  { return ::doupdate(); }
        // Do all outputs to make the physical screen looking like the virtual one

        void SyncDown()  { ::wsyncdown(m_handle); }
        // Propagate the changes down to all descendant windows

        void SyncUp()    { ::wsyncup(m_handle); }
        // Propagate the changes up in the hierarchy

        void SyncCursorUp() { ::wcursyncup(m_handle); }
        // Position the cursor in all ancestor windows corresponding to our setting

        int EnableSync(bool bf) { return ::syncok(m_handle, bf); }
        // If called with bf=TRUE, syncup() is called whenever the window is changed

        void EnableImmediate(bool bf) { ::immedok(m_handle, bf); }
        // If called with bf=TRUE, any change in the window will cause an
        // automatic immediate refresh()

        int            intrflush(bool bf) { return ::intrflush(m_handle, bf); }

        int EnableKeypad(bool bf) { return ::keypad(m_handle, bf); }
        // If called with bf=TRUE, the application will interpret function keys.

        int EnableNoDelay(bool bf) { return ::nodelay(m_handle, bf); }

        int EnableMeta(bool bf) { return ::meta(m_handle, bf); }
        // If called with bf=TRUE, keys may generate 8-Bit characters. Otherwise
        // 7-Bit characters are generated.

        int EnableStandout() { return wstandout(m_handle); }
        // Enable "standout" attributes

        int DisableStandout() { return wstandend(m_handle); }
        // Disable "standout" attributes
        //
        int EnableStandout(bool bf) { return bf ? wstandout(m_handle) : wstandend(m_handle); }

        virtual int  Refresh() { return ::wrefresh(m_handle); }
        // Propagate the changes in this window to the virtual screen and call
        // doupdate(). This is redefined in NCursesPanel.

        virtual int  NoutRefresh() { return ::wnoutrefresh(m_handle); }
        // Propagate the changes in this window to the virtual screen. This is
        // redefined in NCursesPanel.


        // -------------------------------------------------------------------------
        // multiple window control
        // -------------------------------------------------------------------------
        int Overlay(Window& win) {
            return ::overlay(m_handle, win.m_handle); }
        // Overlay this window over win.

        int Overwrite(Window& win) {
            return ::overwrite(m_handle, win.m_handle); }
        // Overwrite win with this window.

        int Copy(Window& win,
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
        bool has_mouse() const;
        // Return TRUE if terminal supports a mouse, FALSE otherwise


        int Height() const { return MaxY() + 1; }

        int Width() const { return MaxX() + 1; }

        int OriginX() const { return getbegx(m_handle); }

        int OriginY() const { return getbegy(m_handle); }

        int CurrentX() const { return getcurx(m_handle); }

        int CurrentY() const { return getcury(m_handle); }

        void Top();

        void Bottom();

        void Show();

        void Hide();

        bool IsHidden()
        {
            return ::panel_hidden(m_panel);
        }

        void Move(int x, int y);

        //TODO: Resize()

        //Window* WhichAbove();

        //Window* WhichBelow();


        int MaxX() const
        {
            return getmaxx(m_handle) == ERR ? ERR : getmaxx(m_handle)-1;
        }

        int MaxY() const
        {
            return getmaxy(m_handle) == ERR ? ERR : getmaxy(m_handle)-1;
        }

        int SetPalette(short fore, short back, short pair);

        int SetPalette(short fore, short back);

        //int SetColor(short pair);

        void AttributeOn(int attr)
        {
            wattron(m_handle, attr);
        }

        void AttributeOff(int attr)
        {
            wattroff(m_handle, attr);
        }

        void Frame()
        {
            box(m_handle, 0, 0);
        }

        void PrintStr(const std::string& str);


        bool isDescendant(Window& win);
        // Return TRUE if win is a descendant of this.

        Point GetParentPoint() const {
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

        WINDOW* GetHandle() const
        {
            return m_handle;
        }

        short GetPair() const;

    protected:
        WINDOW* m_handle = NULL;
        PANEL* m_panel = NULL;


        Window* m_parent  = nullptr;   // parent, if subwindow
        Window* m_subWins = nullptr;   // head of subwindows list
        Window* m_sib     = nullptr;   // next subwindow of parent

    private:
        void killSubwindows();
        bool m_isOwner = true;

};

#endif
