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
    suite->addTest(new TestCaller<DatabaseHandlerTestCase>("test_dataParserBookkeeping", &DatabaseHandlerTestCase::test_dataParserBookkeeping));
    
    return suite;
}

void DatabaseHandlerTestCase::setUp() {
    database_handler = new DatabaseHandler();
    file_entry_statistic = "";
    file_entry_bookkeeping = "";
    setUp_DummyTask();
}

void DatabaseHandlerTestCase::tearDown() {
    delete database_handler;
    if(!(database_handler->dataMiningInquiry()))
    {
        CPPUNIT_ASSERT(true);
    }
    //destructor test
}

void DatabaseHandlerTestCase::setUp_DummyTask() {
    dummy_task = new TaskData;
    dummy_task->id = 1;
    dummy_task->time_appeared = 10;
    dummy_task->time_started = 20;
    dummy_task->time_ended = 30;
    dummy_task->event = 0;
    dummy_task->mode = 0;
    dummy_task->parent = 1;
    dummy_task->time_intercommunication_start = 15;
    dummy_task->time_intercommunication_end = 25;
    dummy_task->rank = 2;
    dummy_task->parameter_size = 3;
    dummy_task->parameters[0] = 3.14;
    dummy_task->parameters[1] = 0.0;
    dummy_task->parameters[2] = 1.999999;
    file_entry_bookkeeping = "1;10;Appeared;Master/Worker;1;15;25;2;3;#";
    file_entry_statistic = "1;3.140000;0.000000;1.999999;#";
}

void DatabaseHandlerTestCase::test_dataMiningInquiry_pointerExist() 
{
    if(database_handler->dataMiningInquiry())
    {
        CPPUNIT_ASSERT(true);
    }
}

void DatabaseHandlerTestCase::test_storeData() {
    database_handler->storeData(dummy_task);
    //check if data in memory
    if(database_handler->stInq)
    {
        CPPUNIT_ASSERT(true);
    }
    //database_handler->stInq;
    //prepare string to compare
}

void DatabaseHandlerTestCase::test_readStatistic() {
    data_Inq = database_handler->readStatistic();
    data_Inq.
    //store and then compare memory
    CPPUNIT_ASSERT(data_Inq->parameter_size == 3);
    CPPUNIT_ASSERT(data_Inq->runtime[0] == 10);
    CPPUNIT_ASSERT(data_Inq->para[0] == 3.14);
    CPPUNIT_ASSERT(data_Inq->para[0] == 0.0);
    CPPUNIT_ASSERT(data_Inq->para[0] == 1.999999);
}

void DatabaseHandlerTestCase::test_dataParserBookkeeping() {
    string test_package = database_handler->dataParserBookkeeping(dummy_task);
    CPPUNIT_ASSERT(test_package == file_entry_bookkeeping);
}

void DatabaseHandlerTestCase::test_dataParserStatistic() {
    string test_package = database_handler->dataParserStatistic(dummy_task);
    CPPUNIT_ASSERT(test_package == file_entry_statistic);
}
//check if stored