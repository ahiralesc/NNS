#define BOOST_TEST_MODULE "Custom hash test"
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <bitset>
#include <operators.hpp>

using namespace std;

BOOST_AUTO_TEST_SUITE(HashOpTEST)

#define  m 65521

/*
 * Custom key hash test
 */

BOOST_AUTO_TEST_CASE( custom_hash_key_test )
{
	bool flag{false};

	// Uso de la llave personalizada
	Key k = { "Heave", "Hell" };

	std::cout << "La llave generada es : " << std::hash<Key>{}(k) <<std::endl;

	if( std::hash<Key>{}(k) == 10163870076410809041 )
		flag = true;

	BOOST_CHECK_EQUAL( flag, true);
}

BOOST_AUTO_TEST_SUITE_END()
