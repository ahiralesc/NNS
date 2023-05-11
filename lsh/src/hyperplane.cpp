#include <cmath>
#include <Eigen/Dense>
#include <iostream>
#include "hyperplane.hpp"

void Hyperplane::preprocess()
{
	/* */
	std::cout << "Buffer size : " << buffer.size( ) << std::endl;
	std::cout << "Shingle size : " << shng_sz << std::endl;

	 /* let n be the total number of points (shingles) */
    unsigned int n = ceil( buffer.size()/shng_sz );
	std::cout << "Number of shingles : " << n << std::endl;

	/* Let k = log_{1/P2}(n), thus k = log_{10}(n) / log_{10}(1/P2) */
	k = ceil( log10(n) / log10(1/P2) );
	std::cout << "k : " << k << std::endl;
	
	/* Let p = ln(1/P1) / ln(1/P2) */
	float p = log(1/P1) / log(1/P2);
	std::cout << "rho : " << p << std::endl;

	/* Let L be the total number of buckets, with L = n^{p} */
	l = ceil( pow(n, p) );
	std::cout << "L : " << l << std::endl;

	/* A random uniform hyperplane matrix */
    Eigen::MatrixXf H = Eigen::MatrixXf::Random(k,shng_sz);

	std::cout << "La matrix N es : " << H << std::endl;

	/*
	1. obtener el buffer 
	2. do {
		 Eigen::VectorXf v = get_shingle();
		 if v.size() != 0
		    Producto punto
			Representacion binaria
		}while(true);
    3. 
	*/

}


void Hyperplane::search()
{


}
