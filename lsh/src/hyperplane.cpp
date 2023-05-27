#include <cmath>
#include <iostream>
#include <random>
#include <set>
#include <climits>
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
	reset();

	/* Partitions the set of points in R^d with random uniform hyperplanes */
	do {
		shingle v = get_shingle();
		if( v.val.size() == 0 )
			 break;

		/* Applies the random hyperplabes to point v */
		Eigen::VectorXf k = H * v.val;

		/* Let key be the binary encoding of the proyection vector k */
		std::string key = encode( k );

		/* Get the list from hash(key) and append the shingle offset */
		T[key].push_back( v.index ); 

	} while(true);
}



void Hyperplane::preprocess()
{
	/* Initiate a random seed for the random number generator */
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(-1, 1);

	 /* let n be the total number of points (shingles) */
    unsigned int n = ceil( buffer.size()/shng_sz );

	/* Let k = log_{1/P2}(n), thus k = log_{10}(n) / log_{10}(1/P2) */
	k = ceil( log10(n) / log10(1/P2) );
	
	/* Let p = ln(1/P1) / ln(1/P2) */
	float p = log(1/P1) / log(1/P2);

	/* Let L be the total number of buckets, with L = n^{p} */
	l = ceil( pow(n, p) );

	/* Create L random uniform matrices and partition the R^d space*/
	for(int i=0; i<l; i++) {
		HPN n;
		n.H = Eigen::MatrixXf::Zero(k, shng_sz).unaryExpr([&](float dummy){return dis(gen);});
		partition( n.H, n.T);
		L.push_back(n);
	}
}



int Hyperplane::hamming(boost::dynamic_bitset<unsigned char> &p, boost::dynamic_bitset<unsigned char> &q) 
{
	return  (p ^ q).count();
}


bool cmp(std::tuple<float, Eigen::VectorXf> & v1, std::tuple<float, Eigen::VectorXf> & v2)
{
    return ( std::get<0>(v1) < std::get<0>(v2) );
}


void Hyperplane::search(std::vector<float> &query, int k )
{
	std::vector<std::tuple<float, Eigen::VectorXf>> nearest_points;
	std::set<int> points;
	
	/* Preparation of the input vector */
	const Eigen::Map<Eigen::VectorXf> v(&query[0],query.size());

	/* Generation of the binary strings */
	for( HPN n : L) {
		int min_dist = INT_MAX;
		std::string min_bucket{};

		/* Compute the proyection vector k and generate the binary encoding q */
		Eigen::VectorXf k = n.H * v;
		boost::dynamic_bitset<unsigned char> q( encode( k ) );
		
		/* Extract the L hast tables T */
		for( const std::pair<const std::string, std::vector<int>> & T : n.T ){
			/* Find the bucket that minimizes the hamming distance */
			boost::dynamic_bitset<unsigned char> p( T.first );
			int dist = hamming(p,q);
			if( dist < min_dist) {
				min_dist = dist;
				min_bucket = T.first;
			}
		}
		/* Extract the list that minimized the hamming distance */
		std::vector<int> & blst = n.T[min_bucket];
		std::copy(blst.begin(), blst.end(), std::inserter(points, points.end()));
	}

	/* Reconstruct the nearest vector points */
	std::vector<Eigen::VectorXf> vectors;
	get_vectors(points, vectors);

	
	/* Select the k nearest vector points */
	for(Eigen::VectorXf p : vectors) {
		float dist = (p - v).norm();
		 std::tuple<float,Eigen::VectorXf> val {dist, p};
		 nearest_points.push_back( val );
	}
	sort(nearest_points.begin(), nearest_points.end(), cmp);

	/* print to stdout the k nearest vectors */
	Eigen::IOFormat CommaInitFmt(Eigen::StreamPrecision, Eigen::DontAlignCols, " ", " ", "", "", "", "");
	int i = 1;
	for(Eigen::VectorXf p : vectors) {
		std::cout << p.format(CommaInitFmt) << std::endl;
		if( i == k ) break;
		i++;
	}
}


void Hyperplane::get_vectors(std::set<int> & points, std::vector<Eigen::VectorXf> & vectors) 
{   
	int bz = buffer.size();

    for (int s : points) {
	 	int e = ( (s + shng_sz) > bz )? bz : s + shng_sz;
		std::vector<float> t(buffer.begin() + s, buffer.begin() + e);
		// Add zero padding if the last vector size is less than k.
		if ( ( s + shng_sz ) > bz ) {
        	int j = ( s + shng_sz ) - bz;
        	int e = t.size() - j;
        	for (int i = e; i < e + j; i++)
            	t.push_back(0);
    	}

		const Eigen::Map<Eigen::VectorXf> vector(&t[0],t.size());
		vectors.push_back(vector); 
    }
}
