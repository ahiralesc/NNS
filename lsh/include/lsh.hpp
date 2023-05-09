#ifndef __LSH_HPP__
#define __LSH_HPP__

#include <string>
#include <vector>
#include <Eigen/Dense>

class LSH
{
    private :
    
	/* Shingling size. The default size is 9 words */
	unsigned int k{}, next{};

	protected:

	/* The vector of text strings */
	std::vector<unsigned int>& buffer;

    public :

    /* class constructor */
    LSH( std::vector<unsigned int> & _buffer, unsigned int _k ) : 
		buffer{ _buffer },
		k { _k },
		next { 0 } {}; 

	/* compute the hash */
	virtual void preprocess() = 0;

	/* searches for string */
	virtual void search() = 0;

	/* gets a shingle of size k */
	Eigen::VectorXf get_shingle( );
};

#endif
