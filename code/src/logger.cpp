#include "logger.hpp"

int current_level = Logger::LEVEL_LOW;

void Logger::log(std::string tag, std::string msg, int level) {
    if (current_level > level) {
        return;
    }
    time_t timer;
    time(&timer);
    struct tm* time = localtime(&timer);
    cout << "[" << time->tm_hour << ":" << time->tm_min << ":" << time->tm_sec << "] " << tag << ": " << msg << endl;
}

void Logger::set_log_level(int level) {
    current_level = level;
}
