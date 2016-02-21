/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FIFOTestCase.cpp
 * Author: fabio
 * 
 * Created on February 19, 2016, 7:25 PM
 */

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "FIFOTestCase.h"

Test* FIFOTestCase::suite() {
    TestSuite* suite = new TestSuite("FIFO test cases");
    suite->addTest(new TestCaller<FIFOTestCase>("test_statistic_based", &FIFOTestCase::test_is_statistic_based));
    suite->addTest(new TestCaller<FIFOTestCase>("test_get_count", &FIFOTestCase::test_get_count));
    suite->addTest(new TestCaller<FIFOTestCase>("test_pop_task", &FIFOTestCase::test_pop_task));
    suite->addTest(new TestCaller<FIFOTestCase>("test_push_new_task", &FIFOTestCase::test_push_new_task));
    suite->addTest(new TestCaller<FIFOTestCase>("test_push_get_next_task", &FIFOTestCase::test_get_next_task));
    
    return suite;
}

void FIFOTestCase::setUp() {
    fifo_queue = new FIFO();
}

void FIFOTestCase::tearDown() {
    delete fifo_queue;
}

void FIFOTestCase::test_is_statistic_based() {
    CPPUNIT_ASSERT(fifo_queue->is_statistic_based() == false);
}

void FIFOTestCase::test_get_count() {
    CPPUNIT_ASSERT(fifo_queue->get_task_count() == 0);
    Task task;
    fifo_queue->push_new_task(task, 0);
    CPPUNIT_ASSERT(fifo_queue->get_task_count() == 1);
    fifo_queue->push_new_task(task, 0);
    fifo_queue->push_new_task(task, 0);
    fifo_queue->push_new_task(task, 0);
    CPPUNIT_ASSERT(fifo_queue->get_task_count() == 4);
}

void FIFOTestCase::test_pop_task() {
    CPPUNIT_ASSERT(fifo_queue->get_task_count() == 0);
    Task task;
    task.parameter_size = 1;
    Task task2;
    task2.parameter_size = 2;
    fifo_queue->push_new_task(task, 0);
    fifo_queue->push_new_task(task2, 0);
    CPPUNIT_ASSERT(fifo_queue->get_task_count() == 2);
    CPPUNIT_ASSERT(fifo_queue->pop_next_task().parameter_size == 1);
    CPPUNIT_ASSERT(fifo_queue->get_task_count() == 1);
    CPPUNIT_ASSERT(fifo_queue->pop_next_task().parameter_size == 2);
    CPPUNIT_ASSERT(fifo_queue->get_task_count() == 0);
}

void FIFOTestCase::test_push_new_task() {
    CPPUNIT_ASSERT(fifo_queue->get_task_count() == 0);
    Task task;
    fifo_queue->push_new_task(task, 0);
    CPPUNIT_ASSERT(fifo_queue->get_task_count() == 1);
    fifo_queue->push_new_task(task, 0);
    CPPUNIT_ASSERT(fifo_queue->get_task_count() == 2);
    fifo_queue->push_new_task(task, 0);
    CPPUNIT_ASSERT(fifo_queue->get_task_count() == 3);
}

void FIFOTestCase::test_get_next_task() {
    CPPUNIT_ASSERT(fifo_queue->get_task_count() == 0);
    Task task;
    task.parameter_size = 1;
    Task task2;
    task2.parameter_size = 2;
    fifo_queue->push_new_task(task, 0);
    fifo_queue->push_new_task(task2, 0);
    CPPUNIT_ASSERT(fifo_queue->get_task_count() == 1);
    CPPUNIT_ASSERT(fifo_queue->get_next_task().parameter_size == 1);
    CPPUNIT_ASSERT(fifo_queue->get_task_count() == 2);
    CPPUNIT_ASSERT(fifo_queue->get_next_task().parameter_size == 1);
    CPPUNIT_ASSERT(fifo_queue->get_task_count() == 2);
}



