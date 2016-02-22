/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LIFOTestCase.cpp
 * Author: fabio
 * 
 * Created on February 22, 2016, 7:28 PM
 */

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "LIFOTestCase.h"

Test* LIFOTestCase::suite() {
    TestSuite* suite = new TestSuite("LIFO test cases");
    suite->addTest(new TestCaller<LIFOTestCase>("test_statistic_based", &LIFOTestCase::test_is_statistic_based));
    suite->addTest(new TestCaller<LIFOTestCase>("test_get_count", &LIFOTestCase::test_get_count));
    suite->addTest(new TestCaller<LIFOTestCase>("test_pop_task", &LIFOTestCase::test_pop_task));
    suite->addTest(new TestCaller<LIFOTestCase>("test_push_new_task", &LIFOTestCase::test_push_new_task));
    suite->addTest(new TestCaller<LIFOTestCase>("test_push_get_next_task", &LIFOTestCase::test_get_next_task));
    
    return suite;
}

void LIFOTestCase::setUp() {
    lifo_queue = new LIFO();
}

void LIFOTestCase::tearDown() {
    delete lifo_queue;
}

void LIFOTestCase::test_is_statistic_based() {
    CPPUNIT_ASSERT(lifo_queue->is_statistic_based() == false);
}

void LIFOTestCase::test_get_count() {
    CPPUNIT_ASSERT(lifo_queue->get_task_count() == 0);
    Task task;
    lifo_queue->push_new_task(task, 0);
    CPPUNIT_ASSERT(lifo_queue->get_task_count() == 1);
    lifo_queue->push_new_task(task, 0);
    lifo_queue->push_new_task(task, 0);
    lifo_queue->push_new_task(task, 0);
    CPPUNIT_ASSERT(lifo_queue->get_task_count() == 4);
}

void LIFOTestCase::test_pop_task() {
    CPPUNIT_ASSERT(lifo_queue->get_task_count() == 0);
    Task task;
    task.parameter_size = 1;
    Task task2;
    task2.parameter_size = 2;
    lifo_queue->push_new_task(task, 0);
    lifo_queue->push_new_task(task2, 0);
    CPPUNIT_ASSERT(lifo_queue->get_task_count() == 2);
    CPPUNIT_ASSERT(lifo_queue->pop_next_task().parameter_size == 2);
    CPPUNIT_ASSERT(lifo_queue->get_task_count() == 1);
    CPPUNIT_ASSERT(lifo_queue->pop_next_task().parameter_size == 1);
    CPPUNIT_ASSERT(lifo_queue->get_task_count() == 0);
}

void LIFOTestCase::test_push_new_task() {
    CPPUNIT_ASSERT(lifo_queue->get_task_count() == 0);
    Task task;
    lifo_queue->push_new_task(task, 0);
    CPPUNIT_ASSERT(lifo_queue->get_task_count() == 1);
    lifo_queue->push_new_task(task, 0);
    CPPUNIT_ASSERT(lifo_queue->get_task_count() == 2);
    lifo_queue->push_new_task(task, 0);
    CPPUNIT_ASSERT(lifo_queue->get_task_count() == 3);
}

void LIFOTestCase::test_get_next_task() {
    CPPUNIT_ASSERT(lifo_queue->get_task_count() == 0);
    Task task;
    task.parameter_size = 1;
    Task task2;
    task2.parameter_size = 2;
    lifo_queue->push_new_task(task, 0);
    lifo_queue->push_new_task(task2, 0);
    CPPUNIT_ASSERT(lifo_queue->get_task_count() == 2);
    CPPUNIT_ASSERT(lifo_queue->get_next_task().parameter_size == 2);
    CPPUNIT_ASSERT(lifo_queue->get_task_count() == 2);
    CPPUNIT_ASSERT(lifo_queue->get_next_task().parameter_size == 2);
    CPPUNIT_ASSERT(lifo_queue->get_task_count() == 2);
}
