/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "DatabaseHandlerTestCase.h"

Test* DatabaseHandlerTestCase::suite() {
    TestSuite* suite = new TestSuite("DatabasHandler test cases");
    suite->addTest(new TestCaller<FIFOTestCase>("test_dataParserBookkeeping", &DatabaseHandlerTestCase::test_dataParserBookkeeping));
    
    return suite;
}

void DatabaseHandlerTestCase::setUp() {
    database_handler = new DatabaseHandler();
}

void DatabaseHandlerTestCase::tearDown() {
    delete database_handler;
    //destructor test
}

void DatabaseHandlerTestCase::test_storeData(TaskData* data) {
    
}

string DatabaseHandlerTestCase::test_dataParserBookkeeping(TaskData* data) {
    CPPUNIT_ASSERT();
}