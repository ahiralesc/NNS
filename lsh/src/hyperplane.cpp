#include <cmath>
#include <Eigen/Dense>
#include <iostream>
#include "hyperplane.hpp"

void Hyperplane::preprocess()
{
	 /* let n be the total number of points (shingles) */
    unsigned int n = ceil( buffer.size()/k );

	/* Let k = log_{1/P2}(n), thus k = log_{10}(n) / log_{10}(1/P2) */
	unsigned int k = ceil( log10(n) / log10(1/P2) );
	
	/* Let p = ln(1/P1) / ln(1/P2) */
	float p = log(1/P1) / log(1/P2);

	/* Let L be the total number of buckets, with L = n^{p} */
	unsigned int L = ceil( pow(n, p) );

    // Eigen::MatrixXf N = Eigen::Matrix

}


void Hyperplane::search()
{


}
