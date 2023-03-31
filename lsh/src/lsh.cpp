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

		TCLAP::CmdLine cmd(
		"NAME \n\
		\t\ lsh - Locality Sensitive Hashing \n\
		SYNPSIS \n\
		\t\ lsh [OPTIONS] FILE \n\
		DESCRIPTION \n\
		\t\ Computes a set of hash tables and stores them in a JSON ontolgy of a given text file. \n\
		\n\
		\t\ -f \t\ The target JSON file. \n\
		\n\
		\t\ -i \t\ The input text file. \n\
		\n\
		\t\ -s \t\ The word shingling length. 9 by default. \n\
		\n\
		EXAMPLES \n\
		\t\ zcat file.gz | lsh -osn file.json \n\
		\t\ lsh -isn file.txt -osn file.json", ' ', "0.1");
 
 	
		// List of value arguments
		TCLAP::ValueArg<string> ofn("f", "file", "the target JSON file", false, "", "string");
		cmd.add( ofn );

		TCLAP::ValueArg<string> ifn("i", "file", "the input text file", false, "", "string");
		cmd.add( ifn );

		TCLAP::ValueArg<int> k("s", "length", "the word shingling length", false, 9, "int");
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

    Hyperplane_LSH lsh{ _isn, _osn, _shingling }; 
    lsh.process();
    
    return 0;
}

/**
*   Coo`ddrdinates the translation process
*/
void GUTTAccept::translate(string &line) {
    TaskEvent event{line,"cvs"};
    // Considera borar id en traza
   auto elem = traces.find(event.job_id);
    if( elem == traces.end() ) {
        Trace trace{};
        trace.insert(event);
        traces.insert(pair<unsigned long long,Trace>(event.job_id,trace));
    } else {
       Trace *trace = &elem->second;
       trace->insert(event);
    }
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
		std::ifstream file( isn );
		if( !file.is_open()) {
			std:cerr << "Could not open input file: " << file << std::endl;
			return EXIT_FAILURE;
		}

		// load the file word strings
		while(file >> word) 
			buffer.push_back(word);

		// close the file
		file.close();
	} else {
        // Parse the input by processing the standard input
        while(cin) {
            getline( cin, input_line );
            
            if( !input_line.empty() ) {
				istringstream ss(str);

                translate( input_line );
			}
        }

        fflush( stdout );
    }


    ofstream afos( aos, std::ofstream::trunc );
    ofstream rfos( ros, std::ofstream::trunc );

    if( !afos || !rfos ) {
        cerr << "Error: could not open file for output" << endl;
        exit(EXIT_FAILURE);
    }
    bool fta = true, ftr = true;

    afos << "{\"traces\":[";
    rfos << "{\"traces\":[";

    // Generating output to files 
    for( map<unsigned long long,ETrace::Trace>::iterator it = traces.begin(); it != traces.end(); ++it ) {
        if((*it).second.isComplete()) {
            if( fta ) {
                afos << (*it).second.to_json();
                fta = false;
            } else 
                afos << "," << std::endl << (*it).second.to_json();
        }else{
            if( ftr ) {
                rfos << (*it).second.to_json();
                ftr = false;
            } else 
                rfos << "," << std::endl << (*it).second.to_json();
        }
       // n++;
    }

    afos << "]}";
    rfos << "]}";
    
    afos.close();
    rfos.close();
}
