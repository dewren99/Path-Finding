/*
 * king-moves.cpp
 *
 * Description: Outputs the sequence of minimum steps to reach the target or impossible if impossible to solve
 *
 *
 * Author: Deniz Evrendilek
 * Date:  22/MAR/2019
 */
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
    pair<unsigned, unsigned> pos;           // Position of the current block on chess board. Holds the values of x and y axis
    pair<unsigned, unsigned> prev_step_pos; // Position of the previous block on chess board. Holds the values of x and y axis
    int distance;                           // Distance from the starting position
    dist_map() : pos({0, 0}), distance(0) {}
    dist_map(pair<unsigned, unsigned> pos, int distance) : pos(pos), distance(distance) {}
};

//vector<vector <int> > dist_map;
//unordered_map<pair<unsigned, unsigned>, int, hash_pair> distmap;

int min_moves(ChessMap &map, const pair<unsigned, unsigned> &start_pos, const pair<unsigned, unsigned> &target, const unsigned &n)
{
    // possible movements for king. For example, if the King is at (2,2) then it can move to (2,2) + (-1,-1) = (1,1) etc.
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

    dist_map arr[n][n]; // User for finding the sequence of minimum moves

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            arr[i][j].distance = 0;         // Make distances 0
            arr[i][j].pos.first = INT_MAX;  // Make coordinates unreachable
            arr[i][j].pos.second = INT_MAX; // Make coordinates unreachable
        }
    }

    queue<dist_map> bfs_queue;              // Creating the queue for BFS algo.
    bfs_queue.push(dist_map(start_pos, 0)); // Pushing the starting position

    while (!bfs_queue.empty()) // while queue is not empty
    {
        dist_map temp = bfs_queue.front(); // peek top and copy its values

        if (temp.pos == target) // if we reached the target position
        {

            bfs_queue.pop(); // delete the top

            // Because we are in "if (temp.pos == target)" statement "arr" is filled with all the vaild(not obstacle or previously visited block/coordinate/position) "dist_map" elements we pushed to our "bfs_queue" queue
            // This big nested for loop goes through every "dist_map" element inside "arr" and checks every neighbor block (chess table block) accessable from the current block based on the Kings movement ability
            // Then, it finds the previous step(previous block) amongst all the neighbor blocks found by checking if previous distance + 1 = current distance
            // After the previous step(aka the ONE step before the current step or ONE block before the current block) is found. The (x,y) value of the block is assigned to "prev_step_pos"
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (arr[i][j].pos.first < n && arr[i][j].pos.second < n)
                    {
                        if (i + 1 < n)
                        {
                            if (arr[i][j].distance == arr[i + 1][j].distance + 1)
                            {
                                arr[i][j].prev_step_pos.first = i + 1;
                                arr[i][j].prev_step_pos.second = j;
                            }
                        }
                        if (i - 1 >= 0)
                        {
                            if (arr[i][j].distance == arr[i - 1][j].distance + 1)
                            {
                                arr[i][j].prev_step_pos.first = i - 1;
                                arr[i][j].prev_step_pos.second = j;
                            }
                        }
                        if (j + 1 < n)
                        {
                            if (arr[i][j].distance == arr[i][j + 1].distance + 1)
                            {
                                arr[i][j].prev_step_pos.first = i;
                                arr[i][j].prev_step_pos.second = j + 1;
                            }
                        }
                        if (j - 1 >= 0)
                        {
                            if (arr[i][j].distance == arr[i][j - 1].distance + 1)
                            {
                                arr[i][j].prev_step_pos.first = i;
                                arr[i][j].prev_step_pos.second = j - 1;
                            }
                        }
                        if (i - 1 >= 0 && j + 1 < n)
                        {
                            if (arr[i][j].distance == arr[i - 1][j + 1].distance + 1)
                            {
                                arr[i][j].prev_step_pos.first = i - 1;
                                arr[i][j].prev_step_pos.second = j + 1;
                            }
                        }
                        if (i + 1 < n && j + 1 < n)
                        {
                            if (arr[i][j].distance == arr[i + 1][j + 1].distance + 1)
                            {
                                arr[i][j].prev_step_pos.first = i + 1;
                                arr[i][j].prev_step_pos.second = j + 1;
                            }
                        }
                        if (i - 1 >= 0 && j - 1 >= 0)
                        {
                            if (arr[i][j].distance == arr[i - 1][j - 1].distance + 1)
                            {
                                arr[i][j].prev_step_pos.first = i - 1;
                                arr[i][j].prev_step_pos.second = j - 1;
                            }
                        }
                        if (i + 1 < n && j - 1 < n)
                        {
                            if (arr[i][j].distance == arr[i + 1][j - 1].distance + 1)
                            {
                                arr[i][j].prev_step_pos.first = i + 1;
                                arr[i][j].prev_step_pos.second = j - 1;
                            }
                        }
                    }
                }
            } //End of nested loop. Explanation for this is written at the start of the nested loop

            unsigned curr_x_coordinate = target.first;
            unsigned curr_y_coordinate = target.second;
            int counter = 0; // since we are not going to count the starting position, the while loop will run the number of minimum moves - 1
            pair<unsigned, unsigned> seq_of_min_moves[temp.distance];

            while (counter < temp.distance)                                                                                                                    // Starts from target position, checks its parent (x,y) coordinates and then goes to that coordinate
            {                                                                                                                                                  // Parent has "current distance-1" distance so if minimum moves is 14 steps it starts from 14th step which is "target" and goes to its parent which is 13th step then 12th and so on
                if (map[arr[curr_x_coordinate][curr_y_coordinate].prev_step_pos.first][arr[curr_x_coordinate][curr_y_coordinate].prev_step_pos.second] != '#') // If coordinates is not pointing to obstacle
                {
                    if (curr_x_coordinate == target.first && curr_y_coordinate == target.second) // saving "target" position
                    {
                        seq_of_min_moves[counter] = arr[curr_x_coordinate][curr_y_coordinate].pos;
                        counter++;
                    }

                    if (arr[curr_x_coordinate][curr_y_coordinate].prev_step_pos != start_pos) // saving minimum steps other than the starting position
                    {
                        seq_of_min_moves[counter] = arr[curr_x_coordinate][curr_y_coordinate].prev_step_pos;
                        counter++;
                    }

                    unsigned temp_x;
                    unsigned temp_y;

                    temp_x = arr[curr_x_coordinate][curr_y_coordinate].prev_step_pos.first;
                    temp_y = arr[curr_x_coordinate][curr_y_coordinate].prev_step_pos.second;

                    curr_x_coordinate = temp_x; // x = parent x
                    curr_y_coordinate = temp_y; // y = parent y
                }
            }
            for (int i = temp.distance - 1; i >= 0; i--)
                cout << seq_of_min_moves[i].first << ", " << seq_of_min_moves[i].second << endl;

            return temp.distance; // return the number of minimum steps
        }

        bfs_queue.pop(); // we can delete the top since we already copied its information to "temp";

        for (int i = 0; i < 8; i++) // The number 8 is the size of cordinates of arrays, namely "x_axis" and "y_axis"
        {
            int x = temp.pos.first + x_axis[i];  // update x axis
            int y = temp.pos.second + y_axis[i]; // update y axis

            if (x >= 0 && x < n && y >= 0 && y < n) // if x and y are valid intigers
            {
                if (!visited[x][y] && map[x][y] != '#') // if (x,y) not visited and its not on obstacle on the "map"
                {
                    pair<unsigned, unsigned> new_pos(x, y);
                    visited[x][y] = true; // mark the (x,y) as visited

                    bfs_queue.push(dist_map(new_pos, temp.distance + 1)); // push the new (x,y) position and increase distance by 1

                    arr[x][y].distance = temp.distance + 1;
                    arr[x][y].pos = new_pos;

                    if (target.first == x && target.second == y) // Stops when target is pushed to stack so It doesnt push any unnessary extra element
                    {                                            // Though its not nessecary to have this if statement or the break call,
                        break;
                    }
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
    // else
    // {
    //     cout << min_moves_output << endl;
    // }
    return 0;
}