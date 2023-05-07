#ifndef __LSH_HPP__
#define __LSH_HPP__

#include <string>
#include <vector>
#include <Eigen/Dense>

class LSH
{
    private :
    
    /* The input stream name (path/file_name) */
    std::string isn;

    /* The output stream name (path/file_name) */
    std::string osn; 

	/* Shingling size. The default size is 9 words */
	int k{}, next{};

	/* User provided probabilities */
	float P1{}, P2{};

	/* The vector of text strings */
	std::vector<float> buffer;

    public :

    /* class constructor */
    LSH( std::string _isn, std::string _osn, int _k, float _P1, float _P2 ) : 
		isn  { _isn }, 
		osn  { _osn }, 
		k { _k },
		P1 { _P1 },
		P2 { _P2 },
		next { 0 } {}; 

    /* Load data. It is assumed that it has been previously transformed to 
	   an integer sequence */
    void load_sequence( );

	/* compute the hash */
	virtual void preprocess() = 0;

	/* searches for string */
	virtual void search() = 0;

	/* gets a shingle of size k */
	Eigen::VectorXf get_shingle( );
};

#endif
