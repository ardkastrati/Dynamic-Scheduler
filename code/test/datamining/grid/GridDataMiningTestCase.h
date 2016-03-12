/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   GridDataMiningTestCase.h
 * Author: jan
 *
 * Created on 11. März 2016, 12:51
 */
 #include "TestFixture.h"

#ifndef GRIDDATAMININGTESTCASE_H
#define GRIDDATAMININGTESTCASE_H

class GridDataMiningTestCase : public TestFixture {
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
private:

};

#endif /* GRIDDATAMININGTESTCASE_H */
