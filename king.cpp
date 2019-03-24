
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
unordered_map<pair<unsigned, unsigned>, int, hash_pair> distmap;

int min_moves(ChessMap &map, const pair<unsigned, unsigned>& start_pos, const pair<unsigned, unsigned>& target, const unsigned& n)
{

    bool visited[n + 1][n + 1]; //since table is nxn we need (n+1)x(n+1)

    visited[start_pos.first][start_pos.second] = true; // Start point is already visited

    for (int i = 0; i < n + 1; i++)
    {
        for (int j = 0; j < n + 1; j++)
        {
            if (i != start_pos.first && j != start_pos.second) // if it is NOT the start point
            {
                visited[i][j] = false;
            }
        }
    }

    //queue<distmap> bfsqueue;
    queue<pair<unsigned,unsigned> > bfsqueue;
    pair<unsigned, unsigned> temp;

    bfsqueue.push(start_pos);

    while (!bfsqueue.empty())
    {
        temp = bfsqueue.front();
        bfsqueue.pop();

        cout<<"Poped: "<< temp.first <<", "<< temp.second <<endl;

        if (temp.first == target.first && temp.second == target.second)
        {
            cout << "found at " << target.first <<", "<< target.second << endl;
            return 1;
        }

        pair<unsigned, unsigned> pos;


        for(int i=0; i<=n-1; i++)
        {
            for(int j=0; j<=n-1; j++)
            {
                if(!visited[i][j] && map[i][j] != '#')
                {
                    //pos = ({i,j)};
                    bfsqueue.push(pair<unsigned,unsigned>({i,j}));
                    visited[i-1][j-1] = true;
                }
            }
        }
    }
    cout<<"Not found?"<<endl;
    return 0;
}

int main()
{
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

    pair<unsigned, unsigned> start; // START POSITION!

    pair<unsigned, unsigned> target; // TARGET POSITION!

    for (unsigned i = 0; i < n; i++)
    {
        for (unsigned j = 0; j < n; j++)
        {
            if (map[i][j] == 'k')
            {
                start = pair<unsigned, unsigned>({i, j});
                //distmap({i,j},0) = pair<unsigned, unsigned>({i, j});
            }

            if (map[i][j] == 'o')
            {
                target = pair<unsigned, unsigned>({i, j});
            }
        }
         if (DEBUG) cout << i << '[' << map[i] << ']' << endl;
    }
    if (DEBUG)
        cout << "The starting position is: " << start.first << ", " << start.second << endl;

    queue<pair<unsigned, unsigned> > bfsqueue;
    pair<unsigned, unsigned> temp;

    bool visited[n + 1][n + 1]; //since table is nxn we need (n+1)x(n+1)

    visited[start.first][start.second] = true; // Start point is already visited

    for (int i = 0; i < n + 1; i++)
    {
        for (int j = 0; j < n + 1; j++)
        {
            if (i != start.first && j != start.second) // if it is NOT the start point
            {
                visited[i][j] = false;
            }
        }
    }

    min_moves(map, start, target, n);

    //bfsqueue.push(start);

    // while (!bfsqueue.empty())
    // {
    //     temp = bfsqueue.front();
    //     bfsqueue.pop();

    //     cout<<"Poped: "<< temp.first <<", "<< temp.second <<endl;

    //     if (temp.first == target.first && temp.second == target.second)
    //     {
    //         cout << "found at " << target.first <<", "<< target.second << endl;
    //         break;
    //     }

    //     pair<unsigned, unsigned> pos;


    //     for(int i=1; i<=n-1; i++)
    //     {
    //         for(int j=1; j<=n-1; j++)
    //         {
    //             if(!visited[i-1][j-1] && map[i][j] != '#')
    //             {
    //                 //pos = ({i,j)};
    //                 bfsqueue.push(pair<unsigned,unsigned>({i,j}));
    //                 visited[i-1][j-1] = true;
    //             }
    //         }
    //     }



    // }

    //-----------//
    //. *** *** .//
    //-----------//

    return 0;
}
