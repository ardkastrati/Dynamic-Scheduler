/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DataStorageTestCase.h
 * Author: jan
 *
 * Created on 11. März 2016, 12:47
 */

#ifndef DATASTORAGETESTCASE_H
#define DATASTORAGETESTCASE_H

#include "TestFixture.h"
#include "../../../src/datamining/grid/DataStorage.h"



using namespace CppUnit;

class DataStorageTestCase : public TestFixture{
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

    void get_dimensions_test();

    void get_offset_test();

    void get_increment_test();

    void time_array_test();

    void correction_vector_test();

  private:
    DataStorage* test_DataStorage;

    int* test_dimensions;

    double* test_offset;

    double* test_increment;
};
#endif /* DATASTORAGETESTCASE_H */

