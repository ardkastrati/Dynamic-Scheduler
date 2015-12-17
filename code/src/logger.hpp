#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <ctime>

using namespace std;

class Logger {
    private:
    public:
        const static int LEVEL_HIGH = 2;
        const static int LEVEL_MED = 1;
        const static int LEVEL_LOW = 0;
        static void log(string tag, string msg, int level);
        static void set_log_level(int level);
};

#endif // LOGGER_H
