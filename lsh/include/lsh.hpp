#ifndef __LSH_HPP__
#define __LSH_HPP__

#include <string>

class LSH
{
    private :
    
    /* The input stream name (path/file_name) */
    std::string isn;

    /* The output stream name (path/file_name) */
    std::string osn; 

		/* Shingling size. The default size is 9 words */
		int shingling;

    public :

    /* class constructor */
    Locality_Sensity_Hashing( 
		    std::string _isn, std::string _osn, int _shingling ) : 
				isn  { _isn }, 
				osn  { _osn }, 
				shingling { _shingling } { };

    /* Does the translation process */
    void process( );
};

#endif
