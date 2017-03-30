#ifndef NCF_NCURSES_WINDOWEXCEPTION_H_
#define NCF_NCURSES_WINDOWEXCEPTION_H_

#include "ncf/ncurses/Window.hpp"
#include "ncf/ncurses/NCException.hpp"

namespace ncf {
namespace ncurses {

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

}
}
#endif
