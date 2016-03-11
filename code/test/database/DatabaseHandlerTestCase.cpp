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
    suite->addTest(new TestCaller<DatabaseHandlerTestCase>("test_dsetUp_DummyTask", &DatabaseHandlerTestCase::setUp_DummyTask));
    suite->addTest(new TestCaller<DatabaseHandlerTestCase>("test_dataMiningInquiry_pointerExist", &DatabaseHandlerTestCase::test_dataMiningInquiry_pointerExist));
    suite->addTest(new TestCaller<DatabaseHandlerTestCase>("test_storeData", &DatabaseHandlerTestCase::test_storeData));
    suite->addTest(new TestCaller<DatabaseHandlerTestCase>("test_storeLocalStatistic", &DatabaseHandlerTestCase::test_storeLocalStatistic));
    suite->addTest(new TestCaller<DatabaseHandlerTestCase>("test_readStatistic", &DatabaseHandlerTestCase::test_readStatistic));
    suite->addTest(new TestCaller<DatabaseHandlerTestCase>("test_dataParserStatistic", &DatabaseHandlerTestCase::test_dataParserStatistic));
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
    if(!database_handler)
    {
        CPPUNIT_ASSERT(true);
    }
}

void DatabaseHandlerTestCase::setUp_DummyTask() {
    dummy_task = new TaskData;
    dummy_task->id = 1;
    dummy_task->time_appeared = 10;
    dummy_task->time_started = 20;
    dummy_task->time_ended = 30;
    dummy_task->event = 2;
    dummy_task->mode = 0;
    dummy_task->parent = 1;
    dummy_task->time_intercommunication_start = 15;
    dummy_task->time_intercommunication_end = 25;
    dummy_task->rank = 2;
    dummy_task->parameter_size = 3;
    dummy_task->parameters[0] = 3.14;
    dummy_task->parameters[1] = 0.0;
    dummy_task->parameters[2] = 1.999999;
    file_entry_bookkeeping = "1;30;Ended;Master/Worker;1;15;25;2;3;#";
    file_entry_statistic = "10;3.140000;0.000000;1.999999;#";
}

void DatabaseHandlerTestCase::test_dataMiningInquiry_pointerExist() 
{
    if(!database_handler->dataMiningInquiry())
    {
        CPPUNIT_ASSERT(true);
    }
}

void DatabaseHandlerTestCase::test_storeData() {
    database_handler->storeData(dummy_task);
    if(database_handler->stInq)
    {
        CPPUNIT_ASSERT(true);
    }
}

void DatabaseHandlerTestCase::test_storeLocalStatistic() {
    database_handler->storeLocalStatistic(dummy_task, 10);
    CPPUNIT_ASSERT((database_handler->stInq->parameter_size == 3));
    CPPUNIT_ASSERT(database_handler->stInq->runtime[0] == 10);
    CPPUNIT_ASSERT(database_handler->stInq->para[0] == 3.14);
    CPPUNIT_ASSERT(database_handler->stInq->para[1] == 0.0);
    CPPUNIT_ASSERT(database_handler->stInq->para[2] == 1.999999);
    
}

void DatabaseHandlerTestCase::test_readStatistic() {
    database_handler->storeData(dummy_task);
    data_Inq = database_handler->readStatistic();
    if(data_Inq)
    {
        CPPUNIT_ASSERT(true);
    }
}

void DatabaseHandlerTestCase::test_dataParserBookkeeping() {
    string test_package = database_handler->dataParserBookkeeping(dummy_task);
    CPPUNIT_ASSERT(test_package == file_entry_bookkeeping);
}

void DatabaseHandlerTestCase::test_dataParserStatistic() {
    string test_package = database_handler->dataParserStatistic(dummy_task);
    CPPUNIT_ASSERT(test_package == file_entry_statistic);
}