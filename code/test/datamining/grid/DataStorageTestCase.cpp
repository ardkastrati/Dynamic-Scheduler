/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   DataStorageTestCase.cpp
 * Author: jan
 *
 * Created on 11. März 2016, 12:47
 */

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "DataStorageTestCase.h"

Test* DataStorageTestCase::suite()
{
    TestSuite* suite = new TestSuite("DataStorage test cases");

    suite->addTest(new TestCaller<DataStorageTestCase>("get_dimensions_test", &DataStorageTestCase::get_dimensions_test));

    suite->addTest(new TestCaller<DataStorageTestCase>("get_offset_test", &DataStorageTestCase::get_offset_test));

    suite->addTest(new TestCaller<DataStorageTestCase>("get_increment_test", &DataStorageTestCase::get_increment_test));

    suite->addTest(new TestCaller<DataStorageTestCase>("time_array_test", &DataStorageTestCase::time_array_test));

    suite->addTest(new TestCaller<DataStorageTestCase>("correction_vector_test", &DataStorageTestCase::correction_vector_test));

    return suite;
}

void DataStorageTestCase::setUp()
{
  test_DataStorage = new DataStorage(3);
  test_dimensions = new int[3];
  test_dimensions[0] = 3;
  test_dimensions[1] = 5;
  test_dimensions[2] = 2;

  test_offset = new double[3];
  test_offset[0] = 7.3;
  test_offset[1] = 9.4;
  test_offset[2] = 10;

  test_increment = new double[3];
  test_increment[0] = 100;
  test_increment[1] = 9;
  test_increment[2] = 0.3;

  test_DataStorage -> set_new_array(test_dimensions, test_offset, test_increment);
}

void DataStorageTestCase::tearDown()
{
  delete test_DataStorage;
  delete test_dimensions;
  delete test_offset;
  delete test_increment;
}

void DataStorageTestCase::get_dimensions_test()
{
  int* dimensions = test_DataStorage -> get_dimensions();
  for(int i = 0; i < 3; i++)
  {
    CPPUNIT_ASSERT(dimensions[i] == test_dimensions[i]);
  }
  delete dimensions;
}

void DataStorageTestCase::get_offset_test()
{
  double* offset = test_DataStorage -> get_offset();
  for(int i = 0; i < 3; i++)
  {
    CPPUNIT_ASSERT(offset[i] == test_offset[i]);
  }
  delete offset;
}

void DataStorageTestCase::get_increment_test()
{
  double* increment = test_DataStorage -> get_increment();
  for(int i = 0; i < 3; i++)
  {
    CPPUNIT_ASSERT(increment[i] == test_increment[i]);
  }
  delete increment;
}

void DataStorageTestCase::time_array_test()
{
  test_DataStorage -> set_time(0, 10);
  test_DataStorage -> set_time(29, 20);

  long time;
  time = test_DataStorage -> get_time(0);
  CPPUNIT_ASSERT(10 == time);

  time = test_DataStorage -> get_time(29);
  CPPUNIT_ASSERT(20 == time);
}

void DataStorageTestCase::correction_vector_test()
{
  test_DataStorage -> set_correction_vector(0, 3.7);
  test_DataStorage -> set_correction_vector(89, 953.27);

  double correction_value;
  correction_value = test_DataStorage -> get_correction_vector(0);
  CPPUNIT_ASSERT(3.7 == correction_value);
  correction_value = test_DataStorage -> get_correction_vector(89);
  CPPUNIT_ASSERT(953.27 == correction_value);
}
