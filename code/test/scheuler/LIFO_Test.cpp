//
// Created by fabio on 19.02.16.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE LIFO
#include <boost/test/unit_test.hpp>

int add (int a, int b) {
    return a + b;
}

BOOST_AUTO_TEST_SUITE(LIFO)

BOOST_AUTO_TEST_CASE(universe)
        {
                BOOST_CHECK(add(1, 2) == 4);
        }

BOOST_AUTO_TEST_SUITE_END()
