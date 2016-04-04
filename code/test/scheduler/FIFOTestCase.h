/**
 * This class is the test class for the FIFO scheduling strategy.
 * 
 * @auhtor Fabio Broghammer
 * @version 1.0
 */

#ifndef FIFOTESTCASE_H
#define FIFOTESTCASE_H

#include "TestFixture.h"

#include "../../src/scheduler/FIFO.h"
#include "../../src/scheduler/SchedulingStrategy.h"

using namespace CppUnit;

class FIFOTestCase : public TestFixture{
public:
        /**
     * Returns a test suite instance that contains all testcases
     * @return a test suite instance
     */
    static Test* suite();
    /**
     * Sets the object for the test up.
     * This is called before every test case.
     */
    void setUp();
    /**
     * Cleans the objects after the test case.
     * This is called after every test case.
     */
    void tearDown();
    /**
     * Tests the pop_task function.
     */
    void test_pop_task();
    /**
     * Tests the push_new_task function.
     */
    void test_push_new_task();
    /**
     * Tests the is_statistic_based function.
     */
    void test_is_statistic_based();
    /**
     * Tests the get_count function.
     */
    void test_get_count();
    /**
     * Tests the get_next_task function
     */
    void test_get_next_task();
private:
    /**
     * The scheduling strategy to to test.
     */
    SchedulingStrategy* fifo_queue;

};

#endif /* FIFOTESTCASE_H */

