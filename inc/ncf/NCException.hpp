#ifndef NCFRAME_NCURSES_EXCEPTION_H_
#define NCFRAME_NCURSES_EXCEPTION_H_

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
};

#endif
