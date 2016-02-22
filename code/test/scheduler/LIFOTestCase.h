/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   LIFOTestCase.h
 * Author: fabio
 *
 * Created on February 22, 2016, 7:28 PM
 */

#ifndef LIFOTESTCASE_H
#define LIFOTESTCASE_H

#include "TestFixture.h"

#include "../../src/scheduler/LIFO.h"

using namespace CppUnit;

class LIFOTestCase : public TestFixture{
public:
    static Test* suite();
    void setUp();
    void tearDown();
    void test_pop_task();
    void test_push_new_task();
    void test_is_statistic_based();
    void test_get_count();
    void test_get_next_task();
private:
    LIFO* lifo_queue;

};

#endif /* LIFOTESTCASE_H */

