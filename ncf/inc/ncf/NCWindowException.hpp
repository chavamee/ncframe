#ifndef NCF_NCURSES_WINDOWEXCEPTION_H_
#define NCF_NCURSES_WINDOWEXCEPTION_H_

#include "ncf/Window.hpp"
#include "ncf/NCException.hpp"

namespace ncf {

class NCWindowException : public NCException
{
    public:
        NCWindowException(const char* msg) :
            NCException(msg)
        {};

        NCWindowException (int err) :
            NCException ("Menu error: ", err)
        {};

        NCWindowException (const char* msg, int err) :
            NCException (msg, err)
        {};

        NCWindowException& operator=(const NCWindowException& rhs)
        {
            if (this != &rhs) {
                NCException::operator=(rhs);
            }
            return *this;
        }

        NCWindowException(const NCWindowException& rhs)
            : NCException(rhs)
        {
        }

        virtual ~NCWindowException()
        {
        }
};

} // namespace ncf
#endif
