/* Copyright 2023 The LSH Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/


#include <iostream>
#include <fstream>
#include <vector>
#include <tclap/CmdLine.h>
#include "lsh.hpp"
#include "hyperplane.hpp"


/* Let isn be the data source input stream (path/file_name) */
std::string isn{};

/* Let osn be the data source output stream (path/file_name) */
std::string osn{}; 

/* Let _k be the shingle size */
unsigned short _k{9};

/* 
	Let P1 be the probability of Pr_H[ h(q) = h(v) ] ≥ P1 and
	Let P2 be the probability of "Pr_H[ h(q) = h(v) ] ≤ P2, such that
	P1 > P2. */
unsigned float _P1{}, _P2{};



using namespace std;



/**
*
*  Parses Command Line Arguments (CLA). 
*  
*/
void parseCLA(int argc, char** argv) 
{
	try{

		TCLAP::CmdLine cmd("NAME \n \t lsh - Locality Sensitive Hashing \n SYNOPSIS \n \t lsh [OPTIONS] FILE \n DESCRIPTION \n \t Given a text file, lsh computes a set of hash tables and stores them in a JSON file.  \n EXAMPLES \n \t zcat file.gz | lsh -osn file.json \n \t lsh -isn file.txt -osn file.json", ' ', "0.1");
 
 	
		// List of value arguments
		TCLAP::ValueArg<string> ofn("f", "json", "The target JSON file that will store the hash tables", false, "", "string");
		cmd.add( ofn );

		TCLAP::ValueArg<string> ifn("i", "txt", "The source text file", false, "", "string");
		cmd.add( ifn );

		TCLAP::ValueArg<unsigned int> k("s", "length", "The word shingling length. By default 9", false, 9, "int");
		cmd.add( k );
		TCLAP::ValueArg<unsigned float> P1("P1", "probability_1", "Pr_H[ h(q) = h(v) ] ≥ P1", false, 0.8, "float");
		cmd.add( P1 );
		TCLAP::ValueArg<unsigned float> P2("P2", "probability_2", "Pr_H[ h(q) = h(v) ] ≤ P2", false, 0.2, "float");
		cmd.add( P2 );

		// Parse the argumnets
		cmd.parse( argc, argv );
		isn = ifn.getValue();
		osn = ofn.getValue();
		_k = k.getValue()-1;
		_P1 = P1.getValue();
		_P2 = P2.getValue();

	}catch(TCLAP::ArgException &e) {
            cerr << "Error: " << e.error() << " for argument " << e.argId() << endl;
            exit(EXIT_FAILURE);
	}
}



/**
*   Parses the text file from stdin or from a file
*/
void load_sequence( std::vector<unsigned int> &buffer  )
{
    string input_line{}, str{};

    // Parse the input by opening the file using a buffered reader
    if( !isn.empty() ) {

        // create the word buffered reader
        ifstream _file( isn );
        if( !_file.is_open()) {
            cerr << "Could not open input file: " << isn << endl;
            exit(EXIT_FAILURE);
        }

        // loads word strings from a text file
        while( _file >> str )
            buffer.push_back(std::stof(str));
        _file.close();
    } else {
        // Parse the input by processing the standard input
        while(cin) {
            while(getline( cin, str, ' ' ))
                buffer.push_back(std::stof(str));
        }

        fflush( stdout );
    }
}



/**
*
*   The main program
*
*/
int main(int argc, char** argv)
{
	std::vector<unsigned int> buffer;

    parseCLA( argc, argv );

	load_sequence( buffer );

    LSH nns = new Hyperplane{ _k, _P1, _P2 }; 

	nns->preprocess( );
    
    return 0;
}
