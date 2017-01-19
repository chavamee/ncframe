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

class NCException : public std::exception {
    public:
        explicit NCException(const std::string& what_arg) :
            m_what{ what_arg }
        {
            def_prog_mode();
        }
        const char *message;
        int errorno;

        NCException (const char* msg, int err)
            : m_what(msg), m_errorno (err)
        {};

        NCException (const char* msg)
            : m_what(msg), m_errorno (E_SYSTEM_ERROR)
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

        virtual const char* classname() const {
            return "NCursesWindow";
        }

        ~NCException()
        {
            reset_prog_mode();
        }

        const char* what() const throw() override
        {
            return m_what.c_str();
        }

    private:
        std::string m_what;
        int m_errorno;
};

#endif
