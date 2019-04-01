
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
    // possible movements for rook. For example, if the Rook is at (2,2) then it can move to (2,2) + (-1,0) = (1,2) etc.
    int x_axis[4] = {-1, 0, 0, 1};
    int y_axis[4] = {0, -1, 1, 0};

    bool visited[n][n]; //since table is nxn, we need nxn array to keep track of visited places

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            visited[i][j] = false; // Make all "not visited"
        }
    }

    visited[start_pos.first][start_pos.second] = true; // Starting position is already visited

    dist_map arr[n][n]; // Used for finding the sequence of minimum moves

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            arr[i][j].distance = 0;         // Make distances 0 (used for printing the sequence of min. moves, not a part of to BFS algo.)
            arr[i][j].pos.first = INT_MAX;  // Make coordinates unreachable (used for printing the sequence of min. moves, not a part of to BFS algo.)
            arr[i][j].pos.second = INT_MAX; // Make coordinates unreachable (used for printing the sequence of min. moves, not a part of to BFS algo.)
        }
    }


    queue<dist_map> bfs_queue;              // Creating the queue for BFS algo.
    bfs_queue.push(dist_map(start_pos, 0)); // Pushing the starting position

    while (!bfs_queue.empty()) // while queue is not empty
    {
        dist_map temp = bfs_queue.front(); // peek top and copy its values
        //bfs_queue.pop(); // I could have written ".pop" here, but to reduce the loop runtime I decided to call two ".pop" functions in two different places

        if (temp.pos == target) // if we reached the target position
        {
            bfs_queue.pop(); // delete the top

            // Because we are in "if (temp.pos == target)" statement "arr" is filled with all the vaild(not obstacle or previously visited block/coordinate/position) "dist_map" elements we pushed to our "bfs_queue" queue
            // This big nested for loop goes through every "dist_map" element inside "arr" and checks every neighbor block (chess table block) accessable from the current block based on the Rooks movement ability
            // Then, it finds the previous step(previous block) amongst all the neighbor blocks found by checking if previous distance + 1 = current distance
            // After the previous step is found. The (x,y) value of the block is assigned to "prev_step_pos". Now, we have access to the location of the previous block for given valid (x,y) coordinates
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (arr[i][j].pos.first < n && arr[i][j].pos.second < n)
                    {
                        int count=0; // Makes sure that we are not exceeding the bounds of the nxn table 
                        int c = i; // We cant change the value of "i" or "j" directly. Otherwise, it will break the nested loop. So, we create a variable to hold the value of "i" or "j".
                        while (c + 1 < n && count<n) // Bound check
                        {
                            if (arr[i][j].distance == arr[c + 1][j].distance + 1)
                            {
                                arr[i][j].prev_step_pos.first = c + 1;
                                arr[i][j].prev_step_pos.second = j;
                            }
                            count++;
                            c++;
                        }
                        c = i;
                        count=0;
                        while (c - 1 >= 0 && count<n) // Bound check
                        {
                            if (arr[i][j].distance == arr[c - 1][j].distance + 1)
                            {
                                arr[i][j].prev_step_pos.first = c - 1;
                                arr[i][j].prev_step_pos.second = j;
                            }
                            c--;
                            count++;
                        }
                        count=0;
                        c = j;
                        while (c + 1 < n && count<n) // Bound check
                        {
                            if (arr[i][j].distance == arr[i][c + 1].distance + 1)
                            {
                                arr[i][j].prev_step_pos.first = i;
                                arr[i][j].prev_step_pos.second = c + 1;
                            }
                            c++;
                            count++;
                        }
                        count=0;
                        c = j;
                        while (c - 1 >= 0 && count<n) // Bound check
                        {
                            if (arr[i][j].distance == arr[i][c - 1].distance + 1)
                            {
                                arr[i][j].prev_step_pos.first = i;
                                arr[i][j].prev_step_pos.second = c - 1;
                            }
                            c--;
                            count++;
                        }
                    }
                }
            } // End of the nested loop. Explanation for this is written at the start of the nested loop

            unsigned curr_x_coordinate = target.first;
            unsigned curr_y_coordinate = target.second;
            int counter = 0;
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
            {
                cout << seq_of_min_moves[i].first << ", " << seq_of_min_moves[i].second << endl;
            }

            // FOR DEBUGGING
            // for (int i = 0; i < n; i++)
            // {
            //     cout << i << " ";
            //     for (int j = 0; j < n; j++)
            //     {
            //         cout << "|" << arr[i][j].distance << "|  ";
            //     }
            //     cout << endl;
            // }
            // for (int i = 0; i < n; i++)
            // {
            //     cout << i << " ";
            //     for (int j = 0; j < n; j++)
            //     {
            //         cout << "|" << arr[i][j].prev_step_pos.first << ", " << arr[i][j].prev_step_pos.second << "|  ";
            //     }
            //     cout << endl;
            // }

            return temp.distance; // return the number of minimum steps
        }

        bfs_queue.pop(); // we can delete the top since we already copied its information to "temp";

        for (int i = 0; i < 4; i++) // The number 4 is the size of cordinates of arrays, namely "x_axis" and "y_axis"
        {
            int x = temp.pos.first + x_axis[i];  // update x axis
            int y = temp.pos.second + y_axis[i]; // update y axis

            while (x + x_axis[i] >= 0 && x + x_axis[i] < n && y + y_axis[i] >= 0 && y + y_axis[i] < n && !visited[x][y] && map[x][y] != '#') //This while loop makes sure that rook is not moving just one block at a time like king
            {                                                                                                                                //It checks if possible to move either horizontally or veritcally more than one block without jumping over obstacles
                if (x == target.first && y == target.second) // If target coordinates found, dont update (x,y) any further and finish the while loop
                {
                    break;
                }

                x += x_axis[i]; // update x axis
                y += y_axis[i]; // update y axis
            }

            if (x >= 0 && x < n && y >= 0 && y < n)// if x and y are valid intigers
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
            if (map[i][j] == 'r')
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