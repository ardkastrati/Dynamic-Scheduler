/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DatabaseTestSuite.h
 * Author: david
 *
 * Created on 8. März 2016, 14:07
 */

#ifndef DATABASETESTSUITE_H
#define DATABASETESTSUITE_H

#include "TestSuite.h"

using namespace CppUnit;

class DatabaseTestSuite {
public:
    /**
     * Returns a test suite instance that contains all tests for the database module.
     * @return a test suite instance
     */
    static TestSuite* suite();
private:

};


#endif /* DATABASETESTSUITE_H */

