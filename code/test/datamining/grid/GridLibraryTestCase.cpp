/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   GridLibraryTestCase.cpp
 * Author: jan
 *
 * Created on 11. März 2016, 12:52
 */

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "GridLibraryTestCase.h"

Test* GridLibraryTestCase::suite()
{
    TestSuite* suite = new TestSuite("GridLibrary test cases");

    suite->addTest(new TestCaller<GridLibraryTestCase>("get_time_test", &GridLibraryTestCase::get_index_test));

    suite->addTest(new TestCaller<GridLibraryTestCase>("get_length_of_vector_test", &GridLibraryTestCase::get_length_of_vector_test));

    suite->addTest(new TestCaller<GridLibraryTestCase>("subtract_array_test", &GridLibraryTestCase::subtract_array_test));

    suite->addTest(new TestCaller<GridLibraryTestCase>("divide_array_test", &GridLibraryTestCase::divide_array_test));

    suite->addTest(new TestCaller<GridLibraryTestCase>("add_array_test", &GridLibraryTestCase::add_array_test));

    suite->addTest(new TestCaller<GridLibraryTestCase>("multiply_array_test", &GridLibraryTestCase::multiply_array_test));

    suite->addTest(new TestCaller<GridLibraryTestCase>("kastrati_value_test", &GridLibraryTestCase::kastrati_value_test));

    return suite;
}

void GridLibraryTestCase::setUp()
{}

void GridLibraryTestCase::tearDown()
{}

void GridLibraryTestCase::get_index_test()
{
  int* index = new int[3];
  index[0] = 4;
  index[1] = 0;
  index[2] = 9;

  int* dimensions = new int[3];
  dimensions[0] = 10;
  dimensions[1] = 50;
  dimensions[2] = 90;

  int one_d_index = GridLibrary::get_index(dimensions,index, 3);

  CPPUNIT_ASSERT(one_d_index == 189);

  delete index;
  delete dimensions;
}

void GridLibraryTestCase::get_length_of_vector_test()
{
  double* vector = new double[2];
  vector[0] = 4;
  vector[0] = 3;
  double length = GridLibrary::get_length_of_vector(vector, 2);

  CPPUNIT_ASSERT(length == 5);

  delete vector;
}

void GridLibraryTestCase::subtract_array_test()
{
  double* first_array = new double[2];
  first_array[0] = 49;
  first_array[1] = 45;

  double* second_array = new double[2];
  second_array[0] = 42;
  second_array[1] = 444;

  double* expected_value = new double[2];
  expected_value[0] = 7;
  expected_value[1] = -399;

  double* value = GridLibrary::subtract_array(first_array, second_array, 2);

  for(int i = 0; i < 2; i++)
  {
    CPPUNIT_ASSERT(value == expected_value);
  }
  delete value;
  delete expected_value;
  delete first_array;
  delete second_array;
}

void GridLibraryTestCase::divide_array_test()
{
  double* first_array = new double[2];
  first_array[0] = 49;
  first_array[1] = 45;

  double* second_array = new double[2];
  second_array[0] = 7;
  second_array[1] = 9;

  double* expected_value = new double[2];
  expected_value[0] = 7;
  expected_value[1] = 5;

  double* value = GridLibrary::divide_array(first_array, second_array, 2);

  for(int i = 0; i < 2; i++)
  {
    CPPUNIT_ASSERT(value == expected_value);
  }
  delete value;
  delete expected_value;
  delete first_array;
  delete second_array;
}

void GridLibraryTestCase::add_array_test()
{
  double* first_array = new double[2];
  first_array[0] = 49;
  first_array[1] = 45;

  double* second_array = new double[2];
  second_array[0] = 7;
  second_array[1] = 9;

  double* expected_value = new double[2];
  expected_value[0] = 56;
  expected_value[1] = 54;

  double* value = GridLibrary::add_array(first_array, second_array, 2);

  for(int i = 0; i < 2; i++)
  {
    CPPUNIT_ASSERT(value == expected_value);
  }
  delete value;
  delete expected_value;
  delete first_array;
  delete second_array;
}

void GridLibraryTestCase::multiply_array_test()
{
  long* first_array = new long[2];
  first_array[0] = 8;
  first_array[1] = 4;

  double* second_array = new double[2];
  second_array[0] = 7;
  second_array[1] = 9;

  double* expected_value = new double[2];
  expected_value[0] = 56;
  expected_value[1] = 36;

  double* value = GridLibrary::multiply_array(first_array, second_array, 2);

  for(int i = 0; i < 2; i++)
  {
    CPPUNIT_ASSERT(value == expected_value);
  }
  delete value;
  delete expected_value;
  delete first_array;
  delete second_array;
}

void GridLibraryTestCase::kastrati_value_test()
{
  double* test = new double[4];
  test[0] = 354;
  test[1] = 3452;
  test[2] = 9736;
  test[3] = 4749;

  double* value = GridLibrary::kastrati_value(test, 4);
  double expected_value[4] = {0.824096, 0.0845104, 0.029964, 0.0614298};
  for(int i = 0; i < 4; i++)
  {
    CPPUNIT_ASSERT(value == expected_value);
  }
}
