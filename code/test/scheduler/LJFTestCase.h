/**
 * This class is the test class for the LJF scheduling strategy.
 * 
 * @auhtor Fabio Broghammer
 * @version 1.0
 */

#ifndef LJFTESTCASE_H
#define LJFTESTCASE_H

#include "TestFixture.h"

#include "../../src/scheduler/LJF.h"
#include "../../src/scheduler/SchedulingStrategy.h"

using namespace CppUnit;

class LJFTestCase : public TestFixture{
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
    SchedulingStrategy* ljf_queue;

};

#endif /* LJFTESTCASE_H */

