#ifndef NCF_NCURSES_PANEL_EXCEPTION_H
#define NCF_NCURSES_PANEL_EXCEPTION_H

#include "ncf/Panel.hpp"
#include "ncf/NCWindowException.hpp"

namespace ncf {

class NCPanelException : public NCWindowException
{
    public:
        NCPanelException (const char* msg) :
            NCWindowException(msg)
        {};

        NCPanelException (int err) :
            NCWindowException ("Menu error: ", err)
        {};

        NCPanelException (const char *msg, int err) :
            NCWindowException (msg, err)
        {};

        NCPanelException& operator=(const NCPanelException& rhs)
        {
            if (this != &rhs) {
                NCWindowException::operator=(rhs);
            }
            return *this;
        }

        NCPanelException(const NCPanelException& rhs)
            : NCWindowException(rhs)
        {
        }

        virtual ~NCPanelException()
        {
        }
};

} // namespace ncf
#endif
