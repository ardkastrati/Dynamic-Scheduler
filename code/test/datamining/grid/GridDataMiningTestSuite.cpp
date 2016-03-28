/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   GridDataMiningTestSuite.cpp
 * Author: jan
 *
 * Created on 11. März 2016, 12:55
 */

#include "GridDataMiningTestSuite.h"


TestSuite* GridDataMiningTestSuite::suite() {
    TestSuite* suite = new TestSuite("Grid test suite");
    suite->addTest(DataStorageTestCase::suite());//TODO
    return suite;
}
