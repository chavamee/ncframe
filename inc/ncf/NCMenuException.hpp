#ifndef NCF_NCURSES_MENUEXCEPTION_H_
#define NCF_NCURSES_MENUEXCEPTION_H_

#include "ncf/Menu.hpp"
#include "ncf/NCException.hpp"

class NCMenuException : public NCException
{
    public:
        NCMenuException (const char *msg, int err) :
            NCException (msg, err)
        {};


        NCMenuException (int err) :
            NCException ("Menu error: ", err)
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

#endif
