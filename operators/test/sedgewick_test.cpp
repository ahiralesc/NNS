#define BOOST_TEST_MODULE "Sedgewick test"
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <bitset>
#include <operators.hpp>

using namespace std;

BOOST_AUTO_TEST_SUITE(HashOpTEST)

#define  m 65521

/*
 * Sedgewick operator ker generation test
 */

BOOST_AUTO_TEST_CASE( sedgewick_key_test )
{
	bool flag{false};

	if(Sedgewick_hash{}("cadena", m) == 63810 )
		flag = true;

	BOOST_CHECK_EQUAL( flag, true);
}

BOOST_AUTO_TEST_SUITE_END()
