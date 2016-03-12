/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   GridDataMiningTestSuite.h
 * Author: jan
 *
 * Created on 11. März 2016, 12:55
 */

#ifndef GRIDDATAMININGTESTSUITE_H
#define GRIDDATAMININGTESTSUITE_H


#include "TestSuite.h"
#include "GridLibraryTestCase.h"
#include "DataStorageTestCase.h"
#include "ArrayHandlerTestCase.h"
#include "GridDataMiningTestCase.h"
using namespace CppUnit;

class GridDataMiningTestSuite {
public:
    /**
     * Returns a test suite instance that contains all tests for the module.
     * @return a test suite instance
     */
    static Test* suite();
private:

};
#endif /* GRIDDATAMININGTESTSUITE_H */
