
#include "mapio.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <queue>
#include <vector>
#include <unordered_map>
#define DEBUG true

using namespace std;


//vector<vector <int> > distmap;
//unordered_map<pair<unsigned, unsigned>, int, hash_pair> distmap;



int main () {
    //. input routine supplied in "mapio.h"
    //.   - access characters in the mapgrid using grid[row][col], 
    //      where 0 <= row, col < n
    ChessMap map;
    cin >> map;
    unsigned n = map.dim();


    //-------------------------------//
    //. *** modify this section *** .//
    //-------------------------------//

    cout << map;

    pair<unsigned, unsigned> start;
    for (unsigned i = 0; i < n; i++) {
        for (unsigned j = 0; j < n; j++) {
            if (map[i][j] == 'k') { start = pair<unsigned, unsigned>({i,j}); }
        }
        // if (DEBUG) cout << '[' << map[i] << ']' << endl;
    }
    if (DEBUG) cout << "The starting position is: " << start.first << ", " << start.second << endl;



    //bfsqueue.push(start);



    //-----------//
    //. *** *** .//
    //-----------//

    return 0;
}

