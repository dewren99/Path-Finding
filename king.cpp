#include "mapio.h"
#include <iostream>
#include <cstdio>
#include <string>
#include <queue>
#include <vector>
#include <unordered_map>
#define DEBUG true

using namespace std;

struct dist_map
{
    pair<unsigned, unsigned> pos;
    int distance;
    dist_map() : pos({0, 0}), distance(0) {}
    dist_map(pair<unsigned, unsigned> pos, int distance) : pos(pos), distance(distance) {}
};

//vector<vector <int> > dist_map;
//unordered_map<pair<unsigned, unsigned>, int, hash_pair> distmap;

int min_moves(ChessMap &map, const pair<unsigned, unsigned> &start_pos, const pair<unsigned, unsigned> &target, const unsigned &n)
{
    // possible movements for king
    int x_axis[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int y_axis[8] = {-1, 1, 0, -1, 1, -1, 1, 0};

    bool visited[n][n]; //since table is nxn, we need nxn array to keep track of visited places

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            visited[i][j] = false; // Make all "not visited"
        }
    }

    visited[start_pos.first][start_pos.second] = true; // Starting position is already visited

    queue<dist_map> bfs_queue;              // Creating the queue for BFS algo.
    bfs_queue.push(dist_map(start_pos, 0)); // Pushing the starting position

    while (!bfs_queue.empty()) // while queue is not empty
    {
        dist_map temp = bfs_queue.front(); // peek top and copy its values

        if (temp.pos == target) // if we reached the target position
        {

            bfs_queue.pop(); // delete the top

            return temp.distance; // return the number of minimum steps
        }

        bfs_queue.pop(); // we can delete the top since we already copied its information to "temp"

        for (int i = 0; i < 8; i++) // The number 8 is the size of cordinates of arrays, namely "x_axis" and "y_axis"
        {
            int x = temp.pos.first + x_axis[i];  // update x axis
            int y = temp.pos.second + y_axis[i]; // update y axis

            if (x >= 0 && x < n && y >= 0 && y < n) // if x and y are valid intigers
            {
                if (!visited[x][y] && map[x][y] != '#') // if (x,y) not visited and its not on obstacle on the "map"
                {
                    //cout<<"ADDING PART x: "<< x<<" y: "<< y <<endl;
                    //arr[x][y] = temp.distance;
                    pair<unsigned, unsigned> new_pos(x, y);
                    visited[x][y] = true;                                 // mark the (x,y) as visited
                    bfs_queue.push(dist_map(new_pos, temp.distance + 1)); // push the new (x,y) position and increase distance by 1
                }
            }
        }
    }
    return -1; // return -1 if impossible
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
            }

            if (map[i][j] == 'o')
            {
                target = pair<unsigned, unsigned>({i, j});
            }
        }
        if (DEBUG)
            cout << i << '[' << map[i] << ']' << endl;
    }
    if (DEBUG)
        cout << "The starting position is: " << start.first << ", " << start.second << endl;

    int min_moves_output = min_moves(map, start, target, n);

    if (min_moves_output == -1)
    {
        cout << "Impossible" << endl;
    }
    else
    {
        cout << min_moves_output << endl;
    }

    return 0;
}