#define BOOST_TEST_MODULE "Avalanche test"
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include <boost/mpl/list.hpp>
#include <iostream>
#include <string>
#include <bitset>

using namespace std;


BOOST_AUTO_TEST_SUITE(LLTEST)


typedef boost::mpl::list<int,long> test_types;

/* Recall, you must edit the hpp header file and implement 
the class methods labeled TODO. For argument I/O requirements
see comments in template hpp file */


BOOST_AUTO_TEST_CASE_TEMPLATE( empty_heap_test, T, test_types )
{
    bitset<2> state;

    state.reset();


    
    state.set(1);

    BOOST_CHECK_EQUAL(state.all(),true);  
}

BOOST_AUTO_TEST_SUITE_END()
