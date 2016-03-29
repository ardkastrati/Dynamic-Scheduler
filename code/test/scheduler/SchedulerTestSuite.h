/**
 * This test suite collects all test for the scheduler module.
 * 
 * @author Fabio Broghammer
 * @version 1.0
 */
#ifndef SCHEDULERTESTSUITE_H
#define SCHEDULERTESTSUITE_H

#include "TestSuite.h"

using namespace CppUnit;

class SchedulerTestSuite {
public:
    /**
     * Returns a test suite instance that contains all tests for the scheduler module.
     * @return a test suite instance
     */
    static TestSuite* suite();
private:

};

#endif /* SCHEDULERTESTSUITE_H */

