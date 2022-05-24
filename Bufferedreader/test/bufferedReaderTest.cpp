#define BOOST_TEST_MODULE "BufferedReader test"
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
##include <boost/mpl/list.hpp>
##include <iostream>
##include <string>
#include <bitset>
#include "BufferedReader.hpp"

using namespace std;


BOOST_AUTO_TEST_SUITE(BRTEST)


typedef boost::mpl::list<int,long> test_types;


BOOST_AUTO_TEST_CASE_TEMPLATE( empty_heap_test, T, test_types )
{
    bitset<2> state;

    state.reset();

    TXTBufferedReader *reader = TXTBufferedReader::getinstance();
    
    state.set(1);

    BOOST_CHECK_EQUAL(state.all(),true);  
}

BOOST_AUTO_TEST_SUITE_END()
