/* Copyright 2023 The LSH Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/


#include "lsh.hpp"


using namespace std;


Eigen::VectorXf LSH::get_shingle() 
{
	int bz{}, s{}, e{};

	Eigen::VectorXf v(shng_sz);
	bz = buffer.size();
	s = next;
	if (s == bz) {
		// a zero size vector is used as the stoppin criterion
		v.resize(0);
		return v;
	}

	// Extract a subvector from the input sequence
	e = ( (s + shng_sz) > bz )? bz : s + shng_sz;
	std::vector<unsigned int> slice(buffer.begin() + s, buffer.begin() + e);
	for(int i = 0; i < slice.size(); i++) 
		v(i) = slice[i];
	
	// Add zero padding if the last vector size is less than k.	
	if ( ( s + shng_sz ) > bz ) {
		int j = ( s + shng_sz ) - bz;
		int e = v.size() - j;
		for (int i = e; i < e + j; i++)
			v(i) = 0;
	} 

	next++;
	
	return v;
}
