/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LJFTestCase.cpp
 * Author: fabio
 * 
 * Created on February 22, 2016, 7:48 PM
 */

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>

#include "LJFTestCase.h"

Test* LJFTestCase::suite() {
    TestSuite* suite = new TestSuite("LJF test cases");
    suite->addTest(new TestCaller<LJFTestCase>("test_statistic_based", &LJFTestCase::test_is_statistic_based));
    suite->addTest(new TestCaller<LJFTestCase>("test_get_count", &LJFTestCase::test_get_count));
    suite->addTest(new TestCaller<LJFTestCase>("test_pop_task", &LJFTestCase::test_pop_task));
    suite->addTest(new TestCaller<LJFTestCase>("test_push_new_task", &LJFTestCase::test_push_new_task));
    suite->addTest(new TestCaller<LJFTestCase>("test_push_get_next_task", &LJFTestCase::test_get_next_task));
    
    return suite;
}

void LJFTestCase::setUp() {
    ljf_queue = new LJF();
}

void LJFTestCase::tearDown() {
    delete ljf_queue;
}

void LJFTestCase::test_is_statistic_based() {
    CPPUNIT_ASSERT(ljf_queue->is_statistic_based() == true);
}

void LJFTestCase::test_get_count() {
    CPPUNIT_ASSERT(ljf_queue->get_task_count() == 0);
    Task task;
    ljf_queue->push_new_task(task, 0);
    CPPUNIT_ASSERT(ljf_queue->get_task_count() == 1);
    ljf_queue->push_new_task(task, 0);
    ljf_queue->push_new_task(task, 0);
    ljf_queue->push_new_task(task, 0);
    CPPUNIT_ASSERT(ljf_queue->get_task_count() == 4);
}

void LJFTestCase::test_pop_task() {
    CPPUNIT_ASSERT(ljf_queue->get_task_count() == 0);
    Task task;
    task.parameter_size = 1;
    Task task2;
    task2.parameter_size = 2;
    ljf_queue->push_new_task(task, 2);
    ljf_queue->push_new_task(task2, 1);
    CPPUNIT_ASSERT(ljf_queue->get_task_count() == 2);
    CPPUNIT_ASSERT(ljf_queue->pop_next_task().parameter_size == 1);
    CPPUNIT_ASSERT(ljf_queue->get_task_count() == 1);
    CPPUNIT_ASSERT(ljf_queue->pop_next_task().parameter_size == 2);
    CPPUNIT_ASSERT(ljf_queue->get_task_count() == 0);
}

void LJFTestCase::test_push_new_task() {
    CPPUNIT_ASSERT(ljf_queue->get_task_count() == 0);
    Task task;
    ljf_queue->push_new_task(task, 0);
    CPPUNIT_ASSERT(ljf_queue->get_task_count() == 1);
    ljf_queue->push_new_task(task, 0);
    CPPUNIT_ASSERT(ljf_queue->get_task_count() == 2);
    ljf_queue->push_new_task(task, 0);
    CPPUNIT_ASSERT(ljf_queue->get_task_count() == 3);
}

void LJFTestCase::test_get_next_task() {
    CPPUNIT_ASSERT(ljf_queue->get_task_count() == 0);
    Task task;
    task.parameter_size = 1;
    Task task2;
    task2.parameter_size = 2;
    ljf_queue->push_new_task(task, 0);
    ljf_queue->push_new_task(task2, 2);
    CPPUNIT_ASSERT(ljf_queue->get_task_count() == 2);
    CPPUNIT_ASSERT(ljf_queue->get_next_task().parameter_size == 2);
    CPPUNIT_ASSERT(ljf_queue->get_task_count() == 2);
    CPPUNIT_ASSERT(ljf_queue->get_next_task().parameter_size == 2);
    CPPUNIT_ASSERT(ljf_queue->get_task_count() == 2);
}

