#include "hyperplane.hpp"
#include <cmath>
#include <iostream>
#include <random>
#include <set>
#include <climits>




std::string Hyperplane::encode(Eigen::VectorXf& v)
{
	std::string str{};

	for (auto x : v) {
		if (x >= 0)
			str.append("1");
		else
			str.append("0");
	}

	return str;
}



void Hyperplane::partition(Eigen::MatrixXf& H, std::unordered_map<std::string, std::vector<int>>& T)
{
	reset();

	/* Partitions the set of points in R^d with random uniform hyperplanes */
	do {
		shingle v = get_shingle();
		
		if (v.val.size() == 0)
			break;

		/* Applies the random hyperplabes to point v */
		Eigen::VectorXf k = H * v.val;

		/* Let key be the binary encoding of the proyection vector k */
		std::string key = encode(k);

		/* Get the list from hash(key) and append the shingle offset */
		T[key].push_back(v.index);

	} while (true);
}



void Hyperplane::preprocess()
{
	/* Initiate a random seed for the random number generator */
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(-1, 1);

	/* let n be the total number of points (shingles) */
	unsigned int n = ceil(buffer.size() / shng_sz);

	/* Let k = log_{1/P2}(n), thus k = log_{10}(n) / log_{10}(1/P2) */
	k = ceil(log10(n) / log10(1 / P2));

	/* Let p = ln(1/P1) / ln(1/P2) */
	float p = log(1 / P1) / log(1 / P2);

	/* Let L be the total number of buckets, with L = n^{p} */
	l = ceil(pow(n, p));

	/* Create L random uniform matrices and partition the R^d space*/
	for (unsigned int i = 0; i < l; i++) {
		HPN n;
		n.H = Eigen::MatrixXf::Zero(k, shng_sz).unaryExpr([&](float dummy) {return dis(gen); });
		partition(n.H, n.T);
		L.push_back(n);
	}
}



int Hyperplane::hamming(boost::dynamic_bitset<unsigned char>& p, boost::dynamic_bitset<unsigned char>& q)
{
	return  (p ^ q).count();
}



bool cmp(std::tuple<float, Eigen::VectorXf>& v1, std::tuple<float, Eigen::VectorXf>& v2)
{
	return (std::get<0>(v1) < std::get<0>(v2));
}


bool bcmp( std::tuple<unsigned int, std::vector<int>> v1, std::tuple<unsigned int, std::vector<int>> v2) {
	return (std::get<0>(v1) < std::get<0>(v2));
}


void Hyperplane::search(std::vector<float>& query, int k)
{
	std::vector<std::tuple<float, Eigen::VectorXf>> nearest_points;
	std::set<int> points;

	/* Preparation of the input vector */
	const Eigen::Map<Eigen::VectorXf> v(&query[0], query.size());

	/* Generation of the binary strings */
	std::vector< std::tuple<unsigned int, std::vector<int>> > buckets{};
	for (HPN n : L) {
		/* Compute the proyection vector k and generate the binary encoding q */
		Eigen::VectorXf k = n.H * v;
		boost::dynamic_bitset<unsigned char> q(encode(k));

		/* Extract T keys and compute the hamming distance */
		for (const std::pair<const std::string, std::vector<int>>& T : n.T) {
			/* Find the bucket that minimizes the hamming distance */
			boost::dynamic_bitset<unsigned char> p(T.first);
			unsigned int dist = hamming(p, q);
			std::tuple<unsigned int, std::vector<int> > bucket{dist, n.T[T.first] };
			buckets.push_back(bucket);
		}
	}

	/* There one or more buckets with equal min hamming distance. Sort and extract the minimum */
	int min = INT_MAX;
	sort(buckets.begin(), buckets.end(), bcmp);
	for (const std::tuple<int, std::vector<int>> bucket : buckets) {
		if (std::get<0>(bucket) <= min) {
			min = std::get<0>(bucket);
			std::vector<int> blst = std::get<1>(bucket);
			std::copy(blst.begin(), blst.end(), std::inserter(points, points.end()));
		}
		else break;
	}

	/* Reconstruct the nearest vector points */
	std::vector<Eigen::VectorXf> vectors;
	get_vectors(points, vectors);

	/* Select the k nearest vector points */
	for (Eigen::VectorXf p : vectors) {
		float dist = (p - v).norm();
		std::tuple<float, Eigen::VectorXf> val{ dist, p };
		nearest_points.push_back(val);
	}
	sort(nearest_points.begin(), nearest_points.end(), cmp);

	/* print to stdout the k nearest vectors */
	Eigen::IOFormat CommaInitFmt(Eigen::StreamPrecision, Eigen::DontAlignCols, " ", " ", "", "", "", "");
	int i = 1;
	for ( std::tuple<float, Eigen::VectorXf> p : nearest_points ) {
		float dist = std::get<0>(p);
		Eigen::VectorXf g = std::get<1>(p);
		std::cout << g.format(CommaInitFmt) << std::endl;
		if (i == k) break;
		i++;
	}
}


void Hyperplane::get_vectors(std::set<int>& points, std::vector<Eigen::VectorXf>& vectors)
{
	unsigned int bz = buffer.size();

	for (unsigned int s : points) {
		int e = ((s + shng_sz) > bz) ? bz : s + shng_sz;
		std::vector<float> t(buffer.begin() + s, buffer.begin() + e);
		// Add zero padding if the last vector size is less than k.
		if ((s + shng_sz) > bz) {
			unsigned int j = (s + shng_sz) - bz;
			unsigned int e = t.size() - j;
			for (unsigned int i = e; i < e + j; i++)
				t.push_back(0);
		}

		const Eigen::Map<Eigen::VectorXf> vector(&t[0], t.size());
		vectors.push_back(vector);
	}
}
