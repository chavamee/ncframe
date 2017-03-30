#ifndef NCFRAME_NCURSES_EXCEPTION_H_
#define NCFRAME_NCURSES_EXCEPTION_H_

extern "C" {
#include <eti.h>
#include <errno.h>
}


extern "C" {
#include <curses.h>
}

#include <stdexcept>
#include <string>

namespace ncf {
namespace ncurses {

class NCException : public std::exception {
    public:
        std::string message;
        int errorno;

        NCException (const char* msg)
            : message(msg), errorno (E_SYSTEM_ERROR)
        {};

        NCException (const char* msg, int err)
            : message(msg), errorno (err)
        {};

        NCException& operator=(const NCException& rhs)
        {
            errorno = rhs.errorno;
            return *this;
        }

        NCException(const NCException& rhs)
            : message(rhs.message), errorno(rhs.errorno)
        {
        }

        virtual ~NCException()
        {
        }

        const char* what() const noexcept override
        {
            return (message + ": " + std::to_string(errorno)).c_str();
        }
};

}
}
#endif
