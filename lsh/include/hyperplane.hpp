#ifndef __HYPERPLANE_LSH__
#define __HyPERPLANE_LSH__

#include <string>
#include <vector>
#include <unordered_map>

class Hyperplane : public LSH {

	// Number of hyperplanes
	int nhyperplanes;

	// Buckets
	std::unordered_map<std::string, std::vector<int>> hash_map;

	public:
	
	void Hyperplane();

};

#endif
