/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: fabio
 *
 * Created on February 19, 2016, 7:21 PM
 */

#include <stdlib.h>
#include "extensions/TestFactoryRegistry.h"
#include "extensions/HelperMacros.h"
#include "ui/text/TestRunner.h"
#include "scheduler/SchedulerTestSuite.h"
 #include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/CompilerOutputter.h>

using namespace std;
using namespace CppUnit;

/*
 * 
 */

int main(int argc, char** argv) {
    TextUi::TestRunner runner;
    TestFactoryRegistry &registry = TestFactoryRegistry::getRegistry();
    TestResult controller;
    TestResultCollector result;
    controller.addListener(&result);
    runner.addTest(registry.makeTest());
    runner.addTest(SchedulerTestSuite::suite());
    runner.run(controller);
    CompilerOutputter outputter(&result, std::cout);
    outputter.write();
    return (result.wasSuccessful() ? 0 : -1);
}
