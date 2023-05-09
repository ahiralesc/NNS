#ifndef __HYPERPLANE_LSH__
#define __HyPERPLANE_LSH__

#include <string>
#include <vector>
#include <unordered_map>
#include "lsh.hpp"

class Hyperplane : public LSH {

	/* Let k ans l be the number of hyperplanes and the number of trails */
	int k{}, l{};

	/* The user provided probabilities */
	float P1{}, P2{};

	// Let B be the map of buckets corresponding to g_l trail.
	std::unordered_map<std::string, std::vector<int>> hash_map;

	public:
	
	Hyperplane(std::vector<unsigned int> & _buffer, unsigned int _k, float _P1, float _P2) : 
		LSH{ _buffer, _k },
		P1{ _P1 },
		P2{ _P2 } {};

	void preprocess();

	void search();
};

#endif
