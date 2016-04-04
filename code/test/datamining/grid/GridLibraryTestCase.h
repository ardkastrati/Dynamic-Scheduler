/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   GridLibraryTestCase.h
 * Author: jan
 *
 * Created on 11. März 2016, 12:52
 */

#ifndef GRIDLIBRARYTESTCASE_H
#define GRIDLIBRARYTESTCASE_H

#include "TestFixture.h"
#include "../../../src/datamining/grid/GridLibrary.h"



using namespace CppUnit;

class GridLibraryTestCase : public TestFixture{
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

    void get_index_test();

    void get_length_of_vector_test();

    void subtract_array_test();

    void divide_array_test();

    void add_array_test();

    void multiply_array_test();

    void kastrati_value_test();
};
#endif /* GRIDLIBRARYTESTCASE_H */
