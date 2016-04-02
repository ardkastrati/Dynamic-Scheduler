/**
 * This file is used to extract the process id and the task number.
 *
 * @author Fabio Broghammer
 * @version 1.0
 */

/**
 * Extracts the process rank from id
 * @param id of the task
 */
inline int get_process_rank(long id) {
    return ((int) (id >> 32));
}

/**
 * Extracts the number of the task from id
 * @param id of the task
 */
inline int get_process_number(long id) {
    return (int) id;
}

/**
 * Get id by rank and number
 * @param rank of the id
 * @param number of the task
 */
inline long get_id_by_rank_and_number(int rank, int number) {
        return (((long) rank) << 32) | number;
};

