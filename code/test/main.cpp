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

using namespace std;
using namespace CppUnit;

/*
 * 
 */

int main(int argc, char** argv) {
    TextUi::TestRunner runner;
    TestFactoryRegistry &registry = TestFactoryRegistry::getRegistry();
    runner.addTest(registry.makeTest());
    runner.addTest(SchedulerTestSuite::suite());
    runner.run();
    return (EXIT_SUCCESS);
}
