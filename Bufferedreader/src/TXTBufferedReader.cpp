/* ==========================================================================
Copyright 2017 The CUTU Authors. All Rights Reserved.
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
    http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
============================================================================= */


/**
*   @file TXTBUfferedReader
*   @section DESCRIPTION
*    
*   A singleton text file buffered reader.
*
*   @author Adan Hirales Carbajal
*   @version 1.0 
*   @date 1
*/

#include <string>
#include <fstream>
#include <iostream>
#include <vector>


using namespace std;



 TXTBufferedReader::TXTBufferedReader(string fname, int _nrows) : nrows{_nrows}  {
        assert(fileName != NULL); 

        ifstrm.open(fname);
        if(!ifstrm) {
            cerr << "Error: could not open the file" << endl;
            exit(EXIT_FAILURE);
        }

        rows.clear();
    };


    ~TXTBufferedReader(){  ifstrm.close(); };


std::string TXTBufferedReader::next() 
{
    string row;
        
        ensureBufferRefill();
        if ( !(done && rows.empty()) ) {{
            row = rows[0];
            rows.erase(rows.beging());
        }
        return row;
    }



void TXTBufferedReader::ensureBufferRefill() 
{
    string row;

    if( rows.empty() && !done ) {
        for(int i=0; i<nrows; i++) {
            getline(ifstrm, row);
            if( ifstrm.eof() ) {
                done = true; 
                return;
            } else
                rows.push_back(row);  
        }
    }
}
