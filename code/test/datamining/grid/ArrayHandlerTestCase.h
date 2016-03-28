/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   ArrayHandlerTestCase.h
 * Author: jan
 *
 * Created on 11. März 2016, 12:43
 */

#ifndef ARRAYHANDLERTESTCASE_H
#define ARRAYHANDLERTESTCASE_H

#include "TestFixture.h"
#include "../../../src/datamining/grid/DataStorage.h"
#include "../../../src/datamining/grid/ArrayHandler.h"



using namespace CppUnit;

class ArrayHandlerTestCase : public TestFixture{
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

    void get_time_test();

    void get_enviroment_index_test();

    void get_dimensions_test();

    void set_new_array_test();

    void insert_at_point_and_get_corrected_distanz_test();

  private:
    ArrayHandler* test_ArrayHandler;

    DataStorage* test_DataStorage;

    int* test_dimensions;

    double* test_offset;

    double* test_increment;
};

#endif /* ARRAYHANDLERTESTCASE_H */
