//
// Created by fabio on 19.02.16.
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE FIFO
#include <boost/test/unit_test.hpp>

int add (int a, int b) {
    return a + b;
}

void test()

        {
                BOOST_CHECK(add(1, 2) == 3);
        }

