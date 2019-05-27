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
    pair<unsigned, unsigned> pos; // Position of current block on chess board. Holds values of x & y axis
    pair<unsigned, unsigned> prev_step_pos; // Position of previous block on chess board. Holds values of x & y axis
    int distance; // Distance from starting position
    dist_map() : pos({0, 0}), distance(0) {}
    dist_map(pair<unsigned, unsigned> pos, int distance) : pos(pos), distance(distance) {}
};

int min_moves(ChessMap &map, const pair<unsigned, unsigned> &start_pos, const pair<unsigned, unsigned> &target, const unsigned &n)
{
    //Possible movements of king. For example, if the King is at (2,2) then it can move to (2,2)+(-1,-1)=(1,1) etc.
    int x_axis[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int y_axis[8] = {-1, 1, 0, -1, 1, -1, 1, 0};

    bool visited[n][n]; //We need nxn array to keep track of visited places
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            visited[i][j] = false; // not visited
        }
    }
    visited[start_pos.first][start_pos.second] = true; //Starting pos. already visited

    dist_map arr[n][n]; // Used for finding sequence of minimum moves
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            arr[i][j].distance = 0; // Make distances 0
            arr[i][j].pos.first = 999999; // Make coordinates unreachable
            arr[i][j].pos.second = 999999; // Make coordinates unreachable
        }
    }

    queue<dist_map> bfs_queue; // Creating the queue for BFS algo.
    bfs_queue.push(dist_map(start_pos, 0)); // Pushing the starting position

    while (!bfs_queue.empty()) // while queue is not empty
    {
        dist_map temp = bfs_queue.front(); // peek top & copy its values

        if (temp.pos == target) // Target x,y is reached
        {
            bfs_queue.pop(); // pop the top
            
            for (int i = 0; i < n; i++)// "arr" is filled with all the vaild(not obstacle & previously visited block/coordinate/position) "dist_map" elements we pushed to our "bfs_queue"
            {// Nested for loop goes through all "dist_map" element inside "arr" and checks every neighbor block accessable from current block based on the Kings movement ability
                for (int j = 0; j < n; j++)// It finds the previous step among other neighbor blocks found by checking if prev. distance+1 = current distance. Then, the (x,y) value of the block is assigned to "prev_step_pos"
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
            } //Explanation is written at up top

            unsigned curr_x_coordinate = target.first;
            unsigned curr_y_coordinate = target.second;
            int counter = 0;
            pair<unsigned, unsigned> seq_of_min_moves[temp.distance]; // For saving the sequence

            while (counter < temp.distance) // Starts from target position, checks its parent (x,y) coordinates and then goes to that coordinate
            { // Parent has "current distance-1" distance. If min. moves is 14 steps it starts from 14th step which is "target" then goes to its parent which is 13th step then 12th and so on
                if (map[arr[curr_x_coordinate][curr_y_coordinate].prev_step_pos.first][arr[curr_x_coordinate][curr_y_coordinate].prev_step_pos.second] != '#') // If coordinates isnt obstacle
                {
                    if (curr_x_coordinate == target.first && curr_y_coordinate == target.second) // saving "target" position
                    {
                        seq_of_min_moves[counter] = arr[curr_x_coordinate][curr_y_coordinate].pos;
                        counter++;
                    }
                    if (arr[curr_x_coordinate][curr_y_coordinate].prev_step_pos != start_pos) // saving minimum steps excluding the starting position
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
            {
                cout << seq_of_min_moves[i].first << ", " << seq_of_min_moves[i].second << endl;
            }
            cout<<"Distance table: "<<endl;
            for(int i=0; i<n; i++)
            {
                for(int j=0; j<n; j++)
                {
                    if(arr[i][j].distance < 10)
                    cout<<" | "<< arr[i][j].distance << "| ";
                    else
                    cout<<" |"<< arr[i][j].distance << "| ";
                }
                cout<<endl;
            }
            cout<<endl;
                        cout<<"Prev. position table: "<<endl;
            for(int i=0; i<n; i++)
            {
                for(int j=0; j<n; j++)
                {
                    cout<<" |"<< arr[i][j].prev_step_pos.first<<','<<arr[i][j].prev_step_pos.second << "| ";
                }
                cout<<endl;
            }
            cout<<endl;

            return temp.distance; // Return number of minimum steps
        }

        bfs_queue.pop(); // Delete the top since we already copied its information to "temp";

        for (int i = 0; i < 8; i++) // 8 is the size of cordinates of arrays
        {
            int x = temp.pos.first + x_axis[i];  // update x axis
            int y = temp.pos.second + y_axis[i]; // update y axis

            if (x >= 0 && x < n && y >= 0 && y < n) // if x and y are valid intigers
            {
                if (!visited[x][y] && map[x][y] != '#') // if x,y not visited and its not on obstacle on the "map"
                {
                    pair<unsigned, unsigned> new_pos(x, y);
                    visited[x][y] = true; // mark the (x,y) as visited

                    bfs_queue.push(dist_map(new_pos, temp.distance + 1)); // push new x,y position and increase distance by 1

                    arr[x][y].distance = temp.distance + 1;
                    arr[x][y].pos = new_pos;

                    if (target.first == x && target.second == y) // Stops when target is pushed to queue so It doesnt push any unnessary extra stuff
                    {
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
    // input routine supplied in "mapio.h"
    // - access characters in the mapgrid using grid[row][col],
    // where 0 <= row, col < n
    ChessMap map;
    cin >> map;
    unsigned n = map.dim();
    //cout << map;
    pair<unsigned, unsigned> start;  // Start (x,y)
    pair<unsigned, unsigned> target; // Target (x,y)

    for (unsigned i = 0; i < n; i++)
    {
        for (unsigned j = 0; j < n; j++)
        {
            if (map[i][j] == 'k')
                start = pair<unsigned, unsigned>({i, j});
            if (map[i][j] == 'o')
                target = pair<unsigned, unsigned>({i, j});
        }
    }
    int min_moves_output = min_moves(map, start, target, n);

    if (min_moves_output == -1)
        cout << "Impossible" << endl;

    return 0;
}