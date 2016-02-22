/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SJFTestCase.h
 * Author: fabio
 *
 * Created on February 22, 2016, 7:36 PM
 */

#ifndef SJFTESTCASE_H
#define SJFTESTCASE_H

#include "TestFixture.h"

#include "../../src/scheduler/SJF.h"
#include "../../src/scheduler/SchedulingStrategy.h"

using namespace CppUnit;

class SJFTestCase : public TestFixture{
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
    SchedulingStrategy* sjf_queue;

};

#endif /* SJFTESTCASE_H */
