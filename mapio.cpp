
#include "mapio.h"

#include <string>
#include <cstring>

using namespace std;


// Desc: Access a row (readonly)
const vector<char> & ChessMap::operator[] (const int index) {
    return map[index];
} // map[i]



// Desc: Access an element (readonly)
const char & ChessMap::operator[] (const pair<unsigned, unsigned> p) {
    return map[p.first][p.second];
} // map[(i,j)]



// Desc: Access the dimensions
const unsigned & ChessMap::dim() {
    return n;
} // dim



// Desc: cout << ChessMap
ostream & operator<<(ostream & os, const ChessMap& rhs) {
    unsigned n = rhs.n;
    for (unsigned i = 0; i < n; i++) {
        cout << rhs.map[i];
        cout << endl;
    }
    return os;
} // operator <<



// Desc: Output a row
ostream & operator<<(ostream & os, const vector<char>& rhs) {
    unsigned n = rhs.size();
    for (unsigned j = 0; j < n; j++) {
        cout << rhs[j];
    }
    return os;
} // operator <<



// Desc: cin >> ChessMap
//  Pre: The input stream must contain a map that follows the spec
//       or else the result is indeterminate.
istream & operator>>(istream & is, ChessMap& rhs) {
    string firstLine;

    // get n
    getline(is, firstLine);
    unsigned n = stoul(firstLine);
    rhs.n = n;

    // build rows
    rhs.map.resize(n);

    // build each row
    for (unsigned i = 0; i < n; i++) {
        string line;
        getline(is, line);
        const char *cstr = line.c_str();
        rhs.map[i] = vector<char>(cstr, cstr+n);
    } // for

    return is;
} // operator >>



