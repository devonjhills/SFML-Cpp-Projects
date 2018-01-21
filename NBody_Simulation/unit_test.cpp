#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <string>
#include "nbody.hpp"

BOOST_AUTO_TEST_CASE(Universe1) {
    /*
    Test the step function and that it advances the position correctly
    */
}

BOOST_AUTO_TEST_CASE(Universe2) {
    /*
    Test the translation from the universe coordinates to the SFML coordinates
    */
}

BOOST_AUTO_TEST_CASE(Universe3) {
    /*
    Test that velocities of the bodies are calculated correctly based on Newtons gravitational law
    */
}
