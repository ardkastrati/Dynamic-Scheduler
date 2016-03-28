/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   ArrayHandlerTestCase.cpp
 * Author: jan
 *
 * Created on 11. März 2016, 12:43
 */

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "ArrayHandlerTestCase.h"

Test* ArrayHandlerTestCase::suite()
{
    TestSuite* suite = new TestSuite("ArrayHandler test cases");

    suite->addTest(new TestCaller<ArrayHandlerTestCase>("get_time_test", &ArrayHandlerTestCase::get_time_test));

    suite->addTest(new TestCaller<ArrayHandlerTestCase>("get_enviroment_index_test", &ArrayHandlerTestCase::get_enviroment_index_test));

    suite->addTest(new TestCaller<ArrayHandlerTestCase>("get_dimensions_test", &ArrayHandlerTestCase::get_dimensions_test));

    suite->addTest(new TestCaller<ArrayHandlerTestCase>("set_new_array_test", &ArrayHandlerTestCase::set_new_array_test));

    suite->addTest(new TestCaller<ArrayHandlerTestCase>("insert_at_point_and_get_corrected_distanz_test", &ArrayHandlerTestCase::insert_at_point_and_get_corrected_distanz_test));

    return suite;
}

void ArrayHandlerTestCase::setUp()
{
  test_DataStorage = new DataStorage(3);
  test_ArrayHandler = new ArrayHandler(3, test_DataStorage);
  test_dimensions = new int[3];
  test_dimensions[0] = 4;
  test_dimensions[1] = 4;
  test_dimensions[2] = 4;

  test_offset = new double[3];
  test_offset[0] = 0;
  test_offset[1] = 0;
  test_offset[2] = 0;

  test_increment = new double[3];
  test_increment[0] = 1;
  test_increment[1] = 1;
  test_increment[2] = 1;

  test_ArrayHandler -> set_new_array(test_dimensions, test_offset, test_increment);
  //get_time_test
  test_DataStorage -> set_time(0, 10);
  test_DataStorage -> set_time(63, 20);
}

void ArrayHandlerTestCase::tearDown()
{
  delete test_ArrayHandler;
  delete test_DataStorage;
  delete test_dimensions;
  delete test_offset;
  delete test_increment;
}

void ArrayHandlerTestCase::get_time_test()
{
  long time;
  int* index = new int[3];
  index[0] = 0;
  index[1] = 0;
  index[2] = 0;

  time = test_ArrayHandler -> get_time(index);
  CPPUNIT_ASSERT(10 == time);

  index[0] = 3;
  index[1] = 3;
  index[2] = 3;
  time = test_ArrayHandler -> get_time(index);
  CPPUNIT_ASSERT(20 == time);
  delete index;
}

void ArrayHandlerTestCase::get_enviroment_index_test()
{
  double* parameter = new double[3];
  parameter[0] = -1;
  parameter[1] = -1;
  parameter[2] = -1;

  int* enviroment_index = test_ArrayHandler -> get_enviroment_index(parameter);
  int expected_values[24] = {0,0,0,
                             0,0,1,
                             0,1,0,
                             0,1,1,
                             1,0,0,
                             1,0,1,
                             1,1,0,
                             1,1,1};
  for(int i = 0; i < 24; i++)
  {
    CPPUNIT_ASSERT(enviroment_index[i] == expected_values[i]);
  }
  delete parameter;
  delete enviroment_index;
}

void ArrayHandlerTestCase::get_dimensions_test()
{
  int* dimensions = test_ArrayHandler -> get_dimensions();
  for(int i = 0; i < 3; i++)
  {
    CPPUNIT_ASSERT(dimensions[i] == test_dimensions[i]);
  }
  delete dimensions;
}

void ArrayHandlerTestCase::set_new_array_test()
{
  int* dimensions = new int[3];
  double* offset = new double[3];
  double* increment = new double[3];

  dimensions[0] = 2;
  dimensions[1] = 2;
  dimensions[2] = 2;

  offset[0] = 0;
  offset[1] = 0;
  offset[2] = 0;

  increment[0] = 1;
  increment[1] = 1;
  increment[2] = 1;

  test_ArrayHandler -> set_new_array(dimensions, increment, offset);

  test_dimensions = test_DataStorage -> get_dimensions();
  test_offset = test_DataStorage -> get_offset();
  test_increment = test_DataStorage -> get_increment();

  for(int i = 0; i < 3; i++)
  {
    CPPUNIT_ASSERT(dimensions[i] == test_dimensions[i]);
    CPPUNIT_ASSERT(offset[i] == test_offset[i]);
    CPPUNIT_ASSERT(increment[i] == increment[i]);
  }
  delete test_dimensions;
  delete test_offset;
  delete test_increment;
  delete dimensions;
  delete offset;
  delete increment;
}

void ArrayHandlerTestCase::insert_at_point_and_get_corrected_distanz_test()
{
  int* index = new int[3];
  index[0] = 0;
  index[1] = 0;
  index[2] = 0;
  double* parameter = new double[3];
  parameter[0] = 0.5;
  parameter[1] = 0.5;
  parameter[2] = 0.5;
  test_ArrayHandler -> insert_at_point(index, parameter, 1337);
  index[0] = 1;
  index[1] = 1;
  index[2] = 1;
  parameter[0] = 0;
  parameter[1] = 0;
  parameter[2] = 0;
  double distance = test_ArrayHandler -> get_corrected_distanz(index, parameter);
  distance = (distance - 0.8990254038 < 0) ? 0.8990254038 - distance : distance - 0.8990254038;
  CPPUNIT_ASSERT(distance < 0.001);
  delete index;
  delete parameter;
}
