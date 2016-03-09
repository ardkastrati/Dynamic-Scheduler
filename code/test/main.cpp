/** 
 * This file includes the main function of the tester for the dynamic scientific scheduler.
 * The tester uses the cppunit port of junit.
 * The implementation of the dynamic scheduler is linked statically to the tester.
 * 
 * @author Fabio Broghammer
 * @version 1.0
 */

#include <stdlib.h>
#include "extensions/TestFactoryRegistry.h"
#include "extensions/HelperMacros.h"
#include "ui/text/TestRunner.h"
#include "scheduler/SchedulerTestSuite.h"
#include "database/DatabaseTestSuite.h"
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/CompilerOutputter.h>

using namespace std;
using namespace CppUnit;

/**
 * The main function, that initializes the framework and start the tests.
 * @param argc command line parameter count
 * @param argv command line parameters
 */
int main(int argc, char** argv) {
    TextUi::TestRunner runner;
    TestFactoryRegistry &registry = TestFactoryRegistry::getRegistry();
    TestResult controller;
    TestResultCollector result;
    controller.addListener(&result);
    runner.addTest(registry.makeTest());
    runner.addTest(SchedulerTestSuite::suite());
    runner.addTest(DatabaseTestSuite::suite());
    runner.run(controller);
    CompilerOutputter outputter(&result, std::cout);
    outputter.write();
    return (result.wasSuccessful() ? 0 : -1);
}
