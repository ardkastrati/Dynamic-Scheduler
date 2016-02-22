/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FIFOTestCase.h
 * Author: fabio
 *
 * Created on February 19, 2016, 7:25 PM
 */

#ifndef FIFOTESTCASE_H
#define FIFOTESTCASE_H

#include "TestFixture.h"

#include "../../src/scheduler/FIFO.h"
#include "../../src/scheduler/SchedulingStrategy.h"

using namespace CppUnit;

class FIFOTestCase : public TestFixture{
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
    SchedulingStrategy* fifo_queue;

};

#endif /* FIFOTESTCASE_H */

