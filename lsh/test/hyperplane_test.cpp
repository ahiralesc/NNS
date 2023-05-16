#define BOOST_TEST_MODULE "Hyperplane test"
#define BOOST_TEST_MAIN 

#include <boost/test/unit_test.hpp>
#include <bitset>
#include <lsh.hpp>
#include <string>
#include <fstream>
#include "hyperplane.hpp"

using namespace std;


string isn = "../../../data/sequence.txt";


/**
*   Parses the text file from stdin or from a file
*
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


BOOST_AUTO_TEST_SUITE(HyperplaneTest)

BOOST_AUTO_TEST_CASE(Hyperplane_test)
{
	unsigned int k = 9;
	float P1 = 0.9, P2 = 0.2;
	bitset<3> state;
	std::vector<unsigned int> buffer;

	load_sequence( buffer );


	state.reset();

	Hyperplane hp{ buffer, k, P1, P2}; 

	hp.preprocess();
	hp.search();

	
	state.set(0);
	state.set(1);
	state.set(2);

	BOOST_CHECK_EQUAL(state.all(), true);
}

BOOST_AUTO_TEST_SUITE_END()
