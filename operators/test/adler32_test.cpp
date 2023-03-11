#define BOOST_TEST_MODULE "Addler test"
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <bitset>
#include <operators.hpp>

using namespace std;

BOOST_AUTO_TEST_SUITE(HashOpTEST)


/*
 * Adler operator key generation test
 */
BOOST_AUTO_TEST_CASE( adler_key_test )
{
	bool flag{false};

	if(Adler32_hash{}("cadena") == 107126775374179)
		flag = true;

	BOOST_CHECK_EQUAL( flag, true);
	
}


/*
 * Sedgewick operator ker generation test
 */

BOOST_AUTO_TEST_CASE( sedgewick_key_test )
{
	bool flag{false};

	if(Sedgewick_hash{}("cadena") == 107126775374179 )
		flag = true;

	BOOST_CHECK_EQUAL( flag, true);
}

BOOST_AUTO_TEST_SUITE_END()
