#ifndef __HYPERPLANE_LSH__
#define __HyPERPLANE_LSH__

#include <string>
#include <vector>
#include <unordered_map>
#include <string>
#include <vector>
#include <Eigen/Dense>
#include <boost/dynamic_bitset.hpp>

#include "lsh.hpp"


struct HPN {
	/* Let H be a random normal matrix */
	Eigen::MatrixXf H;

	/* Let T be the hyperplane partitioned space of points.
	   Only the starting position of the shingled point is stores */
	std::unordered_map< std::string, std::vector<int> *> T;
};


class Hyperplane : public LSH {

	/* Let k = log_{1/P2}(n), thus k = log_{10}(n) / log_{10}(1/P2) */
	unsigned int k{};

	/* Let l be the total number of buckets, with l = n^{p} */
	unsigned int l{};

	/* The user provided probabilities */
	float P1{}, P2{};

	/* Let L be the normal matrix H and the partitiones set of points T*/
	std::vector<HPN> L;

	/* Vector to binary string encoding */
	std::string encode( Eigen::VectorXf & );

	/* Partitions the n-dimensional point space */
	std::unordered_map<std::string, std::vector<int>*>  partition(Eigen::MatrixXf &);

	/* Computes the Hamming distance using boost::dynamic_bitset */
	int hamming( boost::dynamic_bitset<unsigned char>&, boost::dynamic_bitset<unsigned char> &);


	public:
	
	Hyperplane(std::vector<unsigned int> & buffer, unsigned int shng_sz, float _P1, float _P2) : 
		LSH{ buffer, shng_sz },
		P1{ _P1 },
		P2{ _P2 } {};

	void preprocess();

	void search();

	 std::vector<std::vector<unsigned int>> &get_vectors(std::vector<unsigned int> &);

};

#endif
