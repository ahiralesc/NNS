#ifndef __rabin_karp_hpp_
#define __rabin_karp_hpp_

/*
    See Richard. M. Karp and Michael O. Rabin. Efficiet randomized pattern matching algorithms
    IBM J. Res. Develp. Vol 31, No. 2 1987.

    The implementation assumes UTF-8 character set. 4 byte encoding.
*/


using namespace std;


template<typename T>
class Karp_Rabin_Hash {
    private:
        
        char* name() { return "Rabin Karp hash"; }

    public:

        static typedef vector< tuple<int, int> > hash(char *pattern, char *buffer, int ln) {

        } 
        
};

#endif
