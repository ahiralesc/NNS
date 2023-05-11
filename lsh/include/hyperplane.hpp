#ifndef __HYPERPLANE_LSH__
#define __HyPERPLANE_LSH__

#include <string>
#include <vector>
#include <unordered_map>
#include "lsh.hpp"

class Hyperplane : public LSH {

	/* Let k = log_{1/P2}(n), thus k = log_{10}(n) / log_{10}(1/P2) */
	unsigned int k{};

	/* Let l be the total number of buckets, with l = n^{p} */
	unsigned int l{};

	/* The user provided probabilities */
	float P1{}, P2{};

	/* Let B be the map of buckets corresponding to g_l trail. */
	std::unordered_map<std::string, std::vector<int>> hash_map;

	/* List of normal matrices (lnm) */
//	std::list<std::reference_wrapper<Eigen::MatrixXf>> lnm;

	public:
	
	Hyperplane(std::vector<unsigned int> & buffer, unsigned int shng_sz, float _P1, float _P2) : 
		LSH{ buffer, shng_sz },
		P1{ _P1 },
		P2{ _P2 } {};

	void preprocess();

	void search();
};

#endif
