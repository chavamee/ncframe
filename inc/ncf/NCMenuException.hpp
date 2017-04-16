#ifndef NCF_NCURSES_MENU_EXCEPTION_H
#define NCF_NCURSES_MENU_EXCEPTION_H

#include "ncf/Menu.hpp"
#include "ncf/NCException.hpp"

namespace ncf {

class NCMenuException : public NCException
{
    public:
        NCMenuException (const char* msg) :
            NCException(msg)
        {};

        NCMenuException (int err) :
            NCException ("Menu error: ", err)
        {};

        NCMenuException (const char *msg, int err) :
            NCException (msg, err)
        {};

        NCMenuException& operator=(const NCMenuException& rhs)
        {
            if (this != &rhs) {
                NCException::operator=(rhs);
            }
            return *this;
        }

        NCMenuException(const NCMenuException& rhs)
            : NCException(rhs)
        {
        }

        virtual ~NCMenuException()
        {
        }
};

}
#endif
