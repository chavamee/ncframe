#ifndef NCFRAME_COMMON_ARGUMENTS_H_
#define NCFRAME_COMMON_ARGUMENTS_H_

/*
 * Read command line arguments.
 * This should support short flags, long flags, and key/value pairs
 * Essentially, this should represent all of the following:
 *
 * <program> -s --long [--verbose=1 | --verbose 1] [[key] [value (could be nothing)]]
 */
class Arguments
{
    public:
        Arguments();

        Arguments(int argc, char *argv[]);

        /*
         * const T get(const std::string& arg);
         */

        /*
         * void set(const std::string& arg, T value)
         */

        /*
         * void remove(const std::string& arg)
         */
    private:
        void parseArgs();

        int m_argc = 0;
        char *argv[];
};

#endif
