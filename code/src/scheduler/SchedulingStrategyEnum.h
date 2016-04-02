#ifndef CODE_SCHEDULINGSTRATEGYENUM_H
#define CODE_SCHEDULINGSTRATEGYENUM_H

/**
 * This enum enumerates all provided scheduling strategies
 *
 * @author Fabio Broghammer
 * @version 1.0
 */
enum SchedulingStrategyEnum {
    /**
     * First-in first-out policy
     */
    FIFO,
    /**
     * Last-in first-out policy
     */
    LIFO,
    /**
     * Shortest job first policy
     */
    SJF,
    /**
     * Longest job first policy
     */
    LJF
};


#endif //CODE_SCHEDULINGSTRATEGYENUM_H
