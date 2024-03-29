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
std::string iqs{};


/* Let _k be the number of desired neighbors */
unsigned short _k{};

/* 
	Let P1 be the probability of Pr_H[ h(q) = h(v) ] ≥ P1 and
	Let P2 be the probability of "Pr_H[ h(q) = h(v) ] ≤ P2, such that
	P1 > P2. */
float _P1{}, _P2{};



using namespace std;



/**
*
*  Parses Command Line Arguments (CLA). 
*  
*/
void parseCLA(int argc, char** argv) 
{
	try{

		TCLAP::CmdLine cmd("NAME \n \t nns - Nearest neighbor search (NNS)  \n SYNOPSIS \n \t nns [OPTIONS] FILE \n DESCRIPTION \n \t Given a text file, nns finds the k nearest neighbors in an integer encoded  dataset by applying the p-stable distributions method (hyperplane). \n EXAMPLES \n \t zcat file.gz | nns -q query.txt -k 5 -1 0.9 -2 0.3 \n \t cat ../../data/sequence.txt | ./nns -q ../../data/query.txt -k 5 | neighbors.txt", ' ', "0.1");
 	
		// List of value arguments
		TCLAP::ValueArg<string> ifn("i", "input_file", "Integer encoded file", false, "", "string");
		cmd.add( ifn );
		TCLAP::ValueArg<string> iqn("q", "query", "Integer encoded query", true, "", "string");
		cmd.add( iqn );
        TCLAP::ValueArg<float> P2("2", "probability_2", "Pr_H[ h(q) = h(v) ] ≤ P2. Default 0.3 ", false, 0.3, "float");
        cmd.add( P2 );
        TCLAP::ValueArg<float> P1("1", "probability_1", "Pr_H[ h(q) = h(v) ] ≥ P1. Default 0.9", false, 0.9, "float");
        cmd.add( P1 );
		TCLAP::ValueArg<int> k("k", "neighbors", "The k-nearest neighbors. Default 10 if not given", false, 10, "int");
		cmd.add( k );

		// Parse the argumnets
		cmd.parse( argc, argv );
		isn = ifn.getValue();
		iqs = iqn.getValue();
		_k = k.getValue();
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
void load_sequence( std::vector<unsigned int> &buffer, std::string fn )
{
    string input_line{}, str{};

    // Parse the input by opening the file using a buffered reader
    if( !fn.empty() ) {

        // create the word buffered reader
        ifstream _file( fn );
        if( !_file.is_open() ) {
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
	std::vector<unsigned int> query;

    /* Parse the command line arguments */
	parseCLA( argc, argv );

	/* Load the integer encoded sequence from stdin or a file */
	load_sequence( buffer, isn );
	load_sequence( query, iqs );

	/* Estimate the shingle size and cast the query vector to float*/
	unsigned int shingle_sz = query.size();
	std::vector<float> q(query.begin(), query.end());

	Hyperplane hp{ buffer, shingle_sz, _P1, _P2};
	LSH *heuristic = &hp;
	heuristic->preprocess();
	heuristic->search(q, _k);

    return 0;
}
