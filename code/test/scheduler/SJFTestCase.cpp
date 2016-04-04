/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SJFTestCase.cpp
 * Author: fabio
 * 
 * Created on February 22, 2016, 7:36 PM
 */

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "SJFTestCase.h"

Test* SJFTestCase::suite() {
    TestSuite* suite = new TestSuite("SJF test cases");
    suite->addTest(new TestCaller<SJFTestCase>("test_statistic_based", &SJFTestCase::test_is_statistic_based));
    suite->addTest(new TestCaller<SJFTestCase>("test_get_count", &SJFTestCase::test_get_count));
    suite->addTest(new TestCaller<SJFTestCase>("test_pop_task", &SJFTestCase::test_pop_task));
    suite->addTest(new TestCaller<SJFTestCase>("test_push_new_task", &SJFTestCase::test_push_new_task));
    suite->addTest(new TestCaller<SJFTestCase>("test_push_get_next_task", &SJFTestCase::test_get_next_task));
    
    return suite;
}

void SJFTestCase::setUp() {
    sjf_queue = new SJF();
}

void SJFTestCase::tearDown() {
    delete sjf_queue;
}

void SJFTestCase::test_is_statistic_based() {
    CPPUNIT_ASSERT(sjf_queue->is_statistic_based() == true);
}

void SJFTestCase::test_get_count() {
    CPPUNIT_ASSERT(sjf_queue->get_task_count() == 0);
    Task task;
    sjf_queue->push_new_task(task, 0);
    CPPUNIT_ASSERT(sjf_queue->get_task_count() == 1);
    sjf_queue->push_new_task(task, 0);
    sjf_queue->push_new_task(task, 0);
    sjf_queue->push_new_task(task, 0);
    CPPUNIT_ASSERT(sjf_queue->get_task_count() == 4);
}

void SJFTestCase::test_pop_task() {
    CPPUNIT_ASSERT(sjf_queue->get_task_count() == 0);
    Task task;
    task.parameter_size = 1;
    Task task2;
    task2.parameter_size = 2;
    sjf_queue->push_new_task(task, 2);
    sjf_queue->push_new_task(task2, 1);
    CPPUNIT_ASSERT(sjf_queue->get_task_count() == 2);
    CPPUNIT_ASSERT(sjf_queue->pop_next_task().parameter_size == 2);
    CPPUNIT_ASSERT(sjf_queue->get_task_count() == 1);
    CPPUNIT_ASSERT(sjf_queue->pop_next_task().parameter_size == 1);
    CPPUNIT_ASSERT(sjf_queue->get_task_count() == 0);
}

void SJFTestCase::test_push_new_task() {
    CPPUNIT_ASSERT(sjf_queue->get_task_count() == 0);
    Task task;
    sjf_queue->push_new_task(task, 0);
    CPPUNIT_ASSERT(sjf_queue->get_task_count() == 1);
    sjf_queue->push_new_task(task, 0);
    CPPUNIT_ASSERT(sjf_queue->get_task_count() == 2);
    sjf_queue->push_new_task(task, 0);
    CPPUNIT_ASSERT(sjf_queue->get_task_count() == 3);
}

void SJFTestCase::test_get_next_task() {
    CPPUNIT_ASSERT(sjf_queue->get_task_count() == 0);
    Task task;
    task.parameter_size = 1;
    Task task2;
    task2.parameter_size = 2;
    sjf_queue->push_new_task(task, 0);
    sjf_queue->push_new_task(task2, 2);
    CPPUNIT_ASSERT(sjf_queue->get_task_count() == 2);
    CPPUNIT_ASSERT(sjf_queue->get_next_task().parameter_size == 1);
    CPPUNIT_ASSERT(sjf_queue->get_task_count() == 2);
    CPPUNIT_ASSERT(sjf_queue->get_next_task().parameter_size == 1);
    CPPUNIT_ASSERT(sjf_queue->get_task_count() == 2);
}

