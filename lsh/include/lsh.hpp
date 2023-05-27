#ifndef __LSH_HPP__
#define __LSH_HPP__

#include <string>
#include <vector>
#include <Eigen/Dense>

struct shingle {
	 Eigen::VectorXf val;
	 unsigned int    index;
};


class LSH
{
    private :
    
	/* Used by get_shingle */
	unsigned int next{};

	protected:

	/* The vector of text strings */
	std::vector<unsigned int>& buffer;

	/* Shingle size (shng_sz) */
	unsigned int shng_sz{};

    public :

    /* Class constructor */
    LSH( std::vector<unsigned int> & _buffer, unsigned int _shng_sz ) : 
		buffer{ _buffer },
		shng_sz { _shng_sz },
		next { 0 } {}; 

	/* Maps a set of points to a set of hash tables */
	virtual void preprocess() = 0;

	/* Searches a string in the set of hash tables */
	virtual void search(std::vector<float> &) = 0;

	/* gets a shingle of size shng_sz */
	shingle get_shingle();

	/* resets indexes to the start of the buffer */
	void reset();
};

#endif
