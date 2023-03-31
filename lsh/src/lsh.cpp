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
#include <string>
#include <fstream>
#include <vector>
#include <climits>
#include "tclap/CmdLine.h"
#include "buffered_reader.hpp"


using namespace std;
using namespace boost;


/* Parsed number of rows */
int _num_rows = -1;


/* Parsed input stream name */
string _isn{};


/* Parsed output stream name */
string _osn{}; 


/* Parsed non-UTF8 stream name */
string _non_UTF_compliant{}; 


/**
*
*  Parses Command Line Arguments (CLA). 
*  
*/
void parseCLA(int argc, char** argv) 
{
	try{

		CmdLine cmd(
		"NAME \n\
		\t\ lsh - Locality Sensitive Hashing \n\
		SYNPSIS \n\
		\t\ lsh [options] \n\
		DESCRIPTION \n\
		\t\ lsh computes the hash table of UTF8 compliant text files. \n\
		\n\
		\t\ Mandatory arguments are single  hyphen (-). Optional arguments are double hypen (--). See project page for the osn JSON Ontology. \n\
		\n\
		\t\ -isn \t\ the input path and file name of an uncompress text file \n\
		\n\
		\t\ -osn \t\ the output path and file name of the JSON formatted hash table \n\
		\n\
		\t\ --non_compliant \t\ list of lines with non UTF8 compliant characters \n\
		\n\
		\t\ -
		lshguttaccept (Google cluster Usage Task Accept) extracts complete and incomplete execution traces of tasks stored in GUT-Task format (See Google Cluster Usage Traces: format + schema, pp. 8). guttaccept carries out two phases, localization and evaluation. The first phase finds and integrates each task events. The later phase classifies traces as either complete or incomplete. A trace is complete if it contains the initial event, reaches a final event, and all its event transitions are valid, otherwise it is incomplete. The second phase is carried out after the first phase completes. \n\
\n\
Modes of execution: \n\
\tzcat file.csv.gz | guttaccept -a <accepted trace filename>.json -r <rejected trace filename>.json \n\
guttaccept -f file.csv -a <accepted trace filename>.json -r <rejected trace filename>.json", ' ', "0.1");
 
        // List of value arguments
        ValueArg<int> numOfRows("b", "buffer","Number of rows to buffer", false, 1000, "int");
        cmd.add( numOfRows );
 
        ValueArg<string> in_file_name("f", "in_file", "The file name of the Google cluster traces to parse", false, "", "string");
        cmd.add( in_file_name );

        ValueArg<string> accepted_os("a", "accepted", "The file name where the accepted traces will be stored", false, "accept.json", "string");
        cmd.add( accepted_os );

        ValueArg<string> rejected_os("r", "rejected", "The file name where the rejected traces will be stored", false, "reject.json", "string");
        cmd.add( rejected_os );

        // Parse the argumnets
        cmd.parse( argc, argv );
        num_rows = numOfRows.getValue();
        in_file = in_file_name.getValue();
        aos = accepted_os.getValue();
        ros = rejected_os.getValue();
            
        }catch(ArgException &e) {
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

    GUTTAccept parser { num_rows, in_file, aos, ros }; 
    parser.process();
    
    return 0;
}

/**
*   Coordinates the translation process
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
void GUTTAccept::process( )
{
    string input_line;

    // Parse the file from a given file
    if( !in_file.empty() ) {
        csv_buffered_reader reader{in_file, num_rows};
        do{
            input_line = reader.next();
            if( !input_line.empty() )
                translate( input_line );
        } while ( !reader.empty() );
    } else {
        // Parse the file from stdin
        while(cin) {
            getline( cin, input_line );
            
            if( !input_line.empty() )
                translate( input_line );
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
