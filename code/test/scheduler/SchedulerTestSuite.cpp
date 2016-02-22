/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SchedulerTestSuite.cpp
 * Author: fabio
 * 
 * Created on February 21, 2016, 7:43 PM
 */

#include "SchedulerTestSuite.h"
#include "FIFOTestCase.h"
#include "LIFOTestCase.h"
#include "SJFTestCase.h"
#include "LJFTestCase.h"

TestSuite* SchedulerTestSuite::suite() {
    TestSuite* suite = new TestSuite("Scheduler test suite");
    suite->addTest(FIFOTestCase::suite());
    suite->addTest(LIFOTestCase::suite());
    suite->addTest(SJFTestCase::suite());
    suite->addTest(LJFTestCase::suite());
    return suite;
}


