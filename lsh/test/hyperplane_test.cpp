#define BOOST_TEST_MODULE "Hyperplane test"
#define BOOST_TEST_MAIN 

#include <boost/test/unit_test.hpp>
#include <bitset>
#include <lsh.hpp>
#include <hyperplane.hpp>
#include <Eigen/Dense>

using namespace std;

BOOST_AUTO_TEST_SUITE(HyperplaneTest)

BOOST_AUTO_TEST_CASE(Hyperplane_test)
{
	int k = 9;
	bitset<3> state;
	LSH lsh{"../../../data/shingle_test.txt", " ", k};
 	lsh.load_text();/

	state.reset();

	Hyperplane hp{};

	hp.randomHyperplanes();

	
	state.set(0);
	state.set(1);
	state.set(2);

	BOOST_CHECK_EQUAL(state.all(), true);
}

BOOST_AUTO_TEST_SUITE_END()
