#define BOOST_TEST_MODULE "Shingle test"
#define BOOST_TEST_MAIN 

#include <boost/test/unit_test.hpp>
#include <bitset>
#include <lsh.hpp>
#include <Eigen/Dense>
using namespace std;

BOOST_AUTO_TEST_SUITE(ShingleTest)

BOOST_AUTO_TEST_CASE(Shingle_test)
{
	bitset<3> state;
	LSH lsh{};
	state.reset();

	Eigen::Vector4f v = lsh.get_shingle();
	Eigen::Vector4f u << 1, 2, 3, 4, 5, 6, 7, 8, 9;
	if (u == v)
		state.set(0);
	v = lsh.get_shingle();
	Eigen::Vector4f u << 2, 3, 4, 5, 6, 7, 8, 9, 10;
	if (u ==v)
		state.set(1);
	v = lsh.get_shingle();
	Eigen::Vector4f u << 3, 4, 5, 6, 7, 8, 9, 10, 0;
	if (u == v)
		state.set(2);

	BOOST_CHECK_EQUAL(state.all(), true);
}
