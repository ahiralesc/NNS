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
	int k;
	int next;

	/* The vector of text strings */
	std::vector<std::string> buffer;

    public :

    /* class constructor */
    LSH( std::string _isn, std::string _osn, int _k ) : 
		isn  { _isn }, 
		osn  { _osn }, 
		k { _k } { }, 
		next{};

    /* Loas the text file into a vector */
    void load_text( );

	/* compute the hash */
	void process();

	Eigen::Vector3d get_shingle( );
};

#endif
