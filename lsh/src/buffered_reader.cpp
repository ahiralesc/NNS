#include <iostream>
#include "buffered_reader.hpp"

using namespace std;


buffered_reader::buffered_reader(string ifs, long nrows) : 
		num_rows{nrows} {
    rows.clear();
    finalized = false;
    ifstrm.open(ifs);
    if(!ifstrm) {
        cerr << "Error: could not open file" << endl;
        exit(EXIT_FAILURE);
    }
    initialized = true;
}


void buffered_reader::ensureBufferRefill(){
    string row;

    if(rows.empty() && !finalized){
        for(int i=0; i<num_rows; i++) {
            getline(ifstrm,row);
            if(ifstrm.eof()) {
                finalized = true;
                return;
            } else 
                rows.push_back(row);
        }
    }
}


string buffered_reader::next( ) {
    string row;

    ensureBufferRefill();
    if( !empty() ) {
        row = rows[0];
        rows.erase(rows.begin());
    }
    return row;
} 


bool buffered_reader::empty() {
    return finalized && rows.empty();
}
