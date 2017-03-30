#ifndef NCF_NCURSES_PANEL_EXCEPTION_H_
#define NCF_NCURSES_PANEL_EXCEPTION_H_

#include "ncf/ncurses/Panel.hpp"
#include "ncf/ncurses/NCWindowException.hpp"

namespace ncf {
namespace ncurses {

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

}
}
#endif
