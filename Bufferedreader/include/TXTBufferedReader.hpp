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

#ifndef _TXT_Buffered_Reader__
#define _TXT_Buffered_Reader__

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

class TXTBufferedReader {

    public:
    
    static TXTBufferedReader& getInstance() {
        static TXTBufferedReader* singleton = new TXTBufferedReader();
        return *singleton;
    } 


    TXTBufferedReader(string fname) {
        assert(fileName != NULL); 

        ifstrm.open(fname);
        if(!ifstrm) {
            cerr << "Error: could not open the file" << endl;
            exit(EXIT_FAILURE);
        }
    };


    ~TXTBufferedReader(){  ifstrm.close(); };


    string next() {
        string row;
        
        ensureBufferRefill();
        if ( !(done && rows.empty()) ) {{
            row = rows[0];
            rows.erase(rows.beging());
        }
        return row;
    }


    private:
    // The number of rows
    long nrows;

    // A queue holding size rows from the file
    std::vector<string> rows;

    // The input stream
    ifstream ifstrm;

    // Initialization/completion flags
    bool initialized{false}, done{false};


    void ensureBufferRefill() {
        string row;

        if( rows.empty() && !done ) {
            for(int i=0; i<num_rows; i++) {
                getline(ifstrm, row);
                if( ifstrm.eof() ) {
                    done = true; 
                    return;
                } else
                    rows.push_back(row);  
             }
        }
    }

    
    // Delete copy/move so extra instances can't be created/moved.
    TXTBufferedReader(const TXTBufferedReader&) = delete;
    TXTBufferedReader& operator=(const TXTBufferedReader&) = delete;
    TXTBufferedReader(TXTBufferedReader&&) = delete;
    TXTBufferedReader& operator=(TXTBufferedReader&&) = delete;
};


#endif
