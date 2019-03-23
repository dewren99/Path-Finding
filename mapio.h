
#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>

using namespace std;

// Desc: Hash function for pair
struct hash_pair {
    template <class T1, class T2>
        size_t operator()(const pair<T1, T2>& p) const {
            auto hash1 = hash<T1>{}(p.first);
            auto hash2 = hash<T2>{}(p.second);
            return hash1 ^ hash2;
        }
};


class ChessMap {
    private:
        vector< vector< char > > map;
        unsigned n;

    public:
        // Desc: Access a row (readonly)
        const vector<char> & operator[] (const int index);


        // Desc: Access an element (readonly)
        const char & operator[] (const pair<unsigned, unsigned> p);


        // Desc: Access the dimensions
        const unsigned & dim();



        // Desc: I/O functions
        //  Pre: The input stream must contain a map that follows the spec
        //       or else the result is indeterminate.
        friend istream & operator>>(istream & is, ChessMap& rhs);
        friend ostream & operator<<(ostream & os, const ChessMap& rhs);

};


// Desc: Output a row
ostream & operator<<(ostream & os, const vector<char>& rhs);

