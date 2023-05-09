#include <cmath>
#include <Eigen/Dense>
#include <EigenRand/EigenRand>
#include <iostream>
#include "hyperplane.hpp"

void Hyperplane::preprocess()
{
	double p = ceil( buffer.size()/k);
	double h = log(log(p));

	Rand::Vmt19937_64 urng{ 42 };
	Eigen::MatrixXf mat = Rand::balanced<Eigen::MatrixXf>(k,h,urng);

}


void Hyperplane::search()
{


}
