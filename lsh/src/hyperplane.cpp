#include <cmath>
#include <iostream>
#include <random>
#include <set>
#include "hyperplane.hpp"


std::string Hyperplane::encode( Eigen::VectorXf &v ) 
{
	std::string str{};

	for(auto x : v) {            
		if( x >= 0 ) 
			str.append("1");
		else
			str.append("0");
	}

	return str;
}


void Hyperplane::partition( Eigen::MatrixXf &H, std::unordered_map<std::string, std::vector<int>> & T)
{
	/* Shingle offset in file */
	int offset{};

	reset();

	/* Load points (shingles) and partition the space with the random vectors */
	do {
		Eigen::VectorXf v = get_shingle();
		if( v.size() == 0 )
			 break;
		Eigen::VectorXf k = H * v;
		/* Dimensionality reduction via the binary encoding */
		std::string key = encode( k );

		T[key].push_back( offset );

		/* Partition the R^n space 
		if( T.find( key ) == T.end() ) {
			std::vector<int> list {offset};
			T[key] = list;
			//T[key] = new std::vector<int>( {offset} );
		} else
			T[key].push_back( offset ); */

		offset++;
	} while(true);
}


void Hyperplane::preprocess()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(-1, 1);

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

	/* Create L random uniform matrices */
	for(int i=0; i<l; i++) {
		HPN n;
		n.H = Eigen::MatrixXf::Zero(k, shng_sz).unaryExpr([&](float dummy){return dis(gen);});
		std::cout << "\nContenido de H " << std::endl;
		std::cout << n.H;

		partition( n.H, n.T);
		L.push_back(n);
	}
	std::cout << "Termine la fase de preproceamiento " << std::endl;
}


int Hyperplane::hamming(boost::dynamic_bitset<unsigned char> &p, boost::dynamic_bitset<unsigned char> &q) 
{
	return  (p ^ q).count();
}


void Hyperplane::search( )
{
	std::set<int> points;
	
	/* Preparation of the input vector */
	Eigen::VectorXf v(9);
	v << 74, 320, 452, 940, 864, 54, 613, 106, 180;

	/* Generation of the binary strings */
	for( HPN n : L) {
		int min_dist = -1;
		std::string min_bucket{};

		Eigen::VectorXf k = n.H * v;
		std::string key = encode( k );
		boost::dynamic_bitset<unsigned char> q( key );
		/* Extract the L hast tables T */
		for( const std::pair<const std::string, std::vector<int>> & T : n.T ){
			boost::dynamic_bitset<unsigned char> p( T.first );
			int dist = hamming(p,q);
			if( dist < min_dist) {
				min_dist = dist;
				min_bucket = T.first;
			}
		}
		std::cout << "Extrayendo los puntos del bucket con distancia minima"<<std::endl;
		std::vector<int> & blst = n.T[min_bucket];
		std::cout << "Concatenando al conjunto" << std::endl;
		std::copy(blst.begin(), blst.end(), std::inserter(points, points.end()));
	}


	/* print the list of points */
	std::cout << "Indexes similar to point start at locations : " << std::endl;
	for(auto v: points)
		std::cout << v << ", ";
}


std::vector<std::vector<unsigned int>>& Hyperplane::get_vectors( std::vector<unsigned int> &index)
{
	/* Create an empty list of vectors of size zero */
	std::vector<std::vector<unsigned int>> V;
	for(int i=0; i<shng_sz; i++) {
		std::vector<unsigned int> vi;
		V.push_back(vi);
	}

	/* Iterate over the index list and parse the buffer */
	// std::vector<unsigned int> &t = buffet[0]; 
	/* Let i be a value in index, got to buffer[i] and validate the offset
	   and extract shng_sz integers from buffer and push them to t */
	
	return V;
}
