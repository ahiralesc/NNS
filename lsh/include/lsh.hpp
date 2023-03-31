#ifndef __LSH_HPP__
#define __LSH_HPP__

#include <string>
#include <map>
#include <set>


class Locality_Sensitive_Hashing 
{
    private :
    
    /* The number of rows */
    int num_rows;

    /* The input stream name (path/file_name) */
    std::string isn;

    /* The output stream name (path/file_name) */
    std::string osn; 

    /* Lines with non-UTF8 characters */
    std::string non_UTF8_compliant;

    /* TODO:  */
    void translate (std::string&);



    public :

    /* class constructor */
    Locality_Sensity_Hashing( int nrows, std::string isn, std::string osn) : 
        num_rows{ nrows }, in_file { infile }, aos { _aos }, ros{ _ros }  {
    };

    /* Does the translation process */
    void process( );
};

#endif
