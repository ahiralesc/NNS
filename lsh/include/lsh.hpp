#ifndef __LSH_HPP__
#define __LSH_HPP__

#include <string>
#include <vector>
#include <Eigen/Dense>

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

    /* class constructor */
    LSH( std::vector<unsigned int> & _buffer, unsigned int _shng_sz ) : 
		buffer{ _buffer },
		shng_sz { _shng_sz },
		next { 0 } {}; 

	/* compute the hash */
	virtual void preprocess() = 0;

	/* searches for string */
	virtual void search() = 0;

	/* gets a shingle of size shng_sz */
	Eigen::VectorXf get_shingle( );
};

#endif
