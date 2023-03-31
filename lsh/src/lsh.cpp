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
#include <sstream>
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


/**
*
*  Parses Command Line Arguments (CLA). 
*  
*/
void parseCLA(int argc, char** argv) 
{
	try{

		TCLAP::CmdLine cmd("NAME \n \t lsh - Locality Sensitive Hashing \n SYNPSIS \n \t lsh [OPTIONS] FILE \n DESCRIPTION \n \t Computes a set of hash tables and stores them in a JSON ontolgy of a given text file. \n \n \t -f \t The target JSON file. \n \n \t -i \t The input text file. \n \n \t -s \t The word shingling length. 9 by default. \n \n EXAMPLES \n \t zcat file.gz | lsh -osn file.json \n \t lsh -isn file.txt -osn file.json", ' ', "0.1");
 
 	
		// List of value arguments
		TCLAP::ValueArg<std::string> ofn("f", "file", "the target JSON file", false, "", "string");
		cmd.add( ofn );

		TCLAP::ValueArg<std::string> ifn("i", "file", "the input text file", false, "", "string");
		cmd.add( ifn );

		TCLAP::ValueArg<int> k("s", "length", "the word shingling length", false, 9, "int");
		cmd.add( k );

		// Parse the argumnets
		cmd.parse( argc, argv );
		_isn = ifn.getValue();
		_osn = ofn.getValue();
		_shingling = k.getValue();

	}catch(TCLAP::ArgException &e) {
            std::cerr << "Error: " << e.error() << " for argument " << e.argId() << std::endl;
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
*   Coordiantes I/O with the translation process 
*/
void LSH::process( )
{
	std::string input_line, word;
	std::vector<std::string> buffer;

	// Parse the input by opening the file using a buffered reader
	if( !isn.empty() ) {
		
		// create the word buffered reader
		std::ifstream _file( isn );
		if( !_file.is_open()) {
			std::cerr << "Could not open input file: " << isn << std::endl;
			exit(EXIT_FAILURE);
		}

		// load the file word strings
		while(_file >> word) 
			buffer.push_back(word);

		// close the file
		_file.close();
	} else {
        // Parse the input by processing the standard input
        while(std::cin) {
            std::getline( std::cin, input_line );
            
            if( !input_line.empty() ) {
				std::istringstream ss(input_line);

			}
        }

        fflush( stdout );
    }

}
