/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DatabaseHandlerTestCase.h
 * Author: david
 *
 * Created on 8. März 2016, 15:40
 */

#ifndef DATABASEHANDLERTESTCASE_H
#define DATABASEHANDLERTESTCASE_H

#include "TestFixture.h"

#include "../../src/database/DatabaseHandler.h"
#include "../../src/TypesExtern.h"

using namespace CppUnit;

class DatabaseHandlerTestCase : public TestFixture{
public:
    /**
     * Returns a test suite instance that contains all testcases
     * @return a test suite instance
     */
    static Test* suite();
    /**
     * Sets the object for the test up.
     * This ist called before every test case.
     */
    void setUp();
    /**
     * Cleans the objects after the test case.
     * This is called after every test case.
     */
    void tearDown();
    /**
     *
     */
    string test_dataParserBookkeeping(TaskData* data);
    /**
     *
     */
    string test_dataParserStatistic(TaskData* data);
    /**
     *
     */
    void test_storeData(TaskData* data);
    /**
     * 
     */
    void test_storeLocalStatistic(TaskData* data, long runtime);
    /*
     * 
     */
    void test_readTaskData();

private:
    /**
     *
     */
    DatabaseHandler* database_handler;
};

#endif /* DATABASEHANDLERTESTCASE_H */

