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


/* Parsed number of rows */
int _rows{-1};

/* Parsed input stream name */
std::string _isn{};

/* Parsed output stream name */
std::string _osn{}; 

/* Parsed shingling size */
int _shingling{9};

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

		TCLAP::ValueArg<int> k("s", "length", "The word shingling length. By default 9", false, 9, "int");
		cmd.add( k );

		// Parse the argumnets
		cmd.parse( argc, argv );
		_isn = ifn.getValue();
		_osn = ofn.getValue();
		_shingling = k.getValue();

	}catch(TCLAP::ArgException &e) {
            cerr << "Error: " << e.error() << " for argument " << e.argId() << endl;
            exit(EXIT_FAILURE);
	}
}


/**
*   The main program
*/
int main(int argc, char** argv)
{
    parseCLA( argc, argv );

    LSH lsh{ _isn, _osn, _shingling }; 
    lsh.process();
    
    return 0;
}


/**
*   Parses the text file from stdin or a given file
*/
void LSH::process( )
{
	string input_line{}, word{};
	vector<string> buffer;

	// Parse the input by opening the file using a buffered reader
	if( !isn.empty() ) {
		
		// create the word buffered reader
		ifstream _file( isn );
		if( !_file.is_open()) {
			cerr << "Could not open input file: " << isn << endl;
			exit(EXIT_FAILURE);
		}

		// loads word strings from a text file
		while(_file >> word) 
			buffer.push_back(word);
		_file.close();
	} else {
        // Parse the input by processing the standard input
        while(cin) {
        	while(getline( cin, word, ' ' )) 
				buffer.push_back( word );
        }

        fflush( stdout );
    }
}
