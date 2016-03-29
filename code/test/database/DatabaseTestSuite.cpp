/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "DatabaseTestSuite.h"
#include "DatabaseHandlerTestCase.h"

TestSuite* DatabaseTestSuite::suite() {
    TestSuite* suite = new TestSuite("Database test suite");
    suite->addTest(DatabaseHandlerTestCase::suite());
    return suite;
}