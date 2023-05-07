#include <cmath>
#include <math>
#include <Eigen/Dense>
#include <EigenRand/EigenRand>
#include <iostream>

/**
*
* Class constructor
*
*/
void Hyperplane::randomHyperplanes( ) 
{
	// Estimate the number of points.
	double p = ceil(buffer.size()/k);

	// Estimate the number of shingles.
	double h = log(log(p));

	// Initialize a random number generator with seed = 71
	Rand::Vmt19937_64 urng{ 71 };

	// Create the Gaussian matrix wuth N(0,1). Values are between [-1,1]
	Eigen::MatrixXf N = Rand::balanced<MatrixXf>(k,h, urng);

}


void Hyperplane::preprocess()
{

}


void Hyperplane::search()
{


}
