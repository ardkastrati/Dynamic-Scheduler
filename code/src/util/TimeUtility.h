//
// Created by fabio on 07.02.16.
//

#ifndef CODE_TIMEUTILITY_H
#define CODE_TIMEUTILITY_H

#include <chrono>
/**
 * Converts the given floating point variable (in seconds) in a long variable (mirco seconds)
 *
 * @param time_in_seconds time in seconds to be converted
 *
 * @return time in micro seconds
 */
inline long convert_to_micro_seconds(double time_in_seconds)
{
    return (long) (time_in_seconds * 1000000);
}

/**
 * Returns the time in micro seconds
 * TODO: time since when?
 * @return time in micro second
 */
inline long get_time_in_mirco()
{
    auto time = std::chrono::system_clock::now();
    auto since_epoch = time.time_since_epoch();
    auto micros = std::chrono::duration_cast<std::chrono::microseconds>(since_epoch);

    return micros.count();
}

#endif //CODE_TIMEUTILITY_H
