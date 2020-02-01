//
// Created by inbar on 25/01/2020.
//

#ifndef SEARCH__SEARCHALGOS_H_
#define SEARCH__SEARCHALGOS_H_

#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
#include <unordered_map>
#include <cmath>
#include <stack>
#include <cfloat>
#include <cstring>
using namespace std;

// makes a 'visited' bool matrix to match the tested matrix and initial all of the values to be false.
vector<vector<bool>> makeVisited(vector<vector<int>> matrix) {
    vector<vector<bool>> ret;
    vector<bool> row;
    for(int i = 0; i < matrix.size(); i++) {
        for(int j = 0; j < matrix[i].size(); j++) {
            row.push_back(false);
        }
        ret.push_back(row);
        row.clear();
    }
    return ret;
}

struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};


//creates a string of the path
pair<string, int> recString(pair<int,int> start, pair<int,int> end, vector<vector<int>> matrix,
                            unordered_map<pair<int,int>, pair<string, pair<int,int>>, hash_pair> priors) {
    stringstream s;

    if ((end.first == start.first) && (end.second == start.second)) {
        return {"",matrix[end.first][end.second]};
    } else {
        //count += matrix[end.first][end.second];
        pair<string,int> p = recString(start, priors.at(end).second, matrix, priors);
        s << p.first << priors.at(end).first << " (" << p.second + matrix[end.first][end.second] << ") ";
        return {s.str(),p.second+matrix[end.first][end.second]};
    }
}


/*
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                    DFS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

//gets a matrix and point location, prints the location and marks it as visited,
// finds it's neighbors and do the same on them.
stringstream recDFS(vector<vector<int>> matrix, vector<vector<bool>> & visited, pair<int,int> start, pair<int,int> goal, bool *end, int count){
    int i = start.first, j = start.second;
    stringstream s;
    visited[i][j] = true;

    if (!((goal.first == i) && (goal.second == j))) {
        //checks neighbors
        if (((i + 1 < matrix.size()) && (visited[i + 1][j] == false) && (matrix[i+1][j]>=0))  && !*end) {
            count+=matrix[i+1][j];
            s<<"Down (" << count<<") "<<recDFS(matrix, visited,{i+1, j} , goal, end, count).str();
            return s;
        }
        if (((j + 1 < matrix[i].size()) && (visited[i][j + 1] == false) && (matrix[i][j+1]>=0)) && !*end) {
            count+=matrix[i][j+1];
            s<<"Right (" << count<<") "<<recDFS(matrix, visited, {i, j+1}, goal, end,count).str();
            return s;
        }
        if (((i > 0) && (visited[i - 1][j] == false) && (matrix[i-1][j]>=0)) && !*end) {
            count+=matrix[i-1][j];
            s<<"Up (" << count<<") "<<recDFS(matrix, visited, {i-1, j}, goal,end,count).str();
            return s;
        }
        if (((j > 0) && (visited[i][j - 1] == false) && (matrix[i][j-1]>=0)) && !*end) {
            count+=matrix[i][j-1];
            s<<"Left (" << count<<") "<<recDFS(matrix, visited,{i, j-1}, goal,end,count).str();
            return s;
        }
    } else {
        *end = true;
        return s;
    }
}

// create visited matrix and activates the recursive dfs function recDfs
string dfs(vector<vector<int>> matrix, pair<int,int> start, pair<int, int> goal) {
    vector<vector<bool>> visited = makeVisited(matrix);
    return recDFS(matrix, visited, start,goal, new bool(false),matrix[start.first][start.second]).str();
}


/*
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                    BFS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

string bfs(vector<vector<int>> matrix, pair<int,int> start, pair<int,int> goal) {
    queue<pair<int,int>> next;
    vector<vector<bool>>visited = makeVisited(matrix);
    unordered_map<pair<int,int>, pair<string, pair<int,int>>, hash_pair> priors;
    next.push(start);
    visited[start.first][start.second] = true;
    while (!next.empty()) {
        int i = next.front().first;
        int j = next.front().second;
        if (!((goal.first == i) && goal.second == j)) {
            next.pop();

            if ((i + 1 < matrix.size()) && (visited[i + 1][j] == false) && (matrix[i+1][j]>=0)) {
                priors[{i+1,j}] = {"Down",{i,j}};
                next.push({i + 1, j});
                visited[i + 1][j] = true;
            }
            if ((j + 1 < matrix[i].size()) && (visited[i][j + 1] == false) && (matrix[i][j+1]>=0)) {
                priors[{i,j+1}] = {"Right",{i,j}};
                next.push({i, j + 1});
                visited[i][j + 1] = true;
            }
            if ((i > 0) && (visited[i - 1][j] == false) && (matrix[i-1][j]>=0)) {
                priors[{i-1,j}] = {"Up",{i,j}};
                next.push({i - 1, j});
                visited[i - 1][j] = true;
            }
            if ((j > 0) && (visited[i][j - 1] == false) && (matrix[i][j-1]>=0)) {
                priors[{i,j-1}] = {"Left",{i,j}};
                next.push({i, j - 1});
                visited[i][j - 1] = true;
            }
        } else {
            return recString(start, goal, matrix, priors).first;
        }
    }
}


/*
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                    BEFS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

class Compare {
    vector<vector<int>> matrix;
    static Compare *c;

public:
    vector<vector<int>> getMatrix() {
        return this->instance()->matrix;
    }
    int get(pair<int,int> location) {
        return this->getMatrix()[location.first][location.second];
    }
    void setMatrix(vector<vector<int>> matrix) {
        this->matrix = matrix;
    }
    void  set(pair<int,int> place, int value) {
        this->instance()->matrix[place.first][place.second] = value;
    }
    int getRows() {
        return this->instance()->matrix.size();
    }
    int getCols() {
        return this->instance()->matrix[0].size();
    }
    static Compare *instance() {
        if (!c) {
            c = new Compare;
        }
        return c;
    }


    int operator()(const pair<int, int> & p1, const pair<int, int> & p2) {
        return this->get(p1) > this->get(p2);
    }

    int operator()(const pair<pair<int, int>, pair<int, double>> & p1, const pair<pair<int, int>, pair<int, double>> & p2) {
        return (p1.second.first + p1.second.second) > (p2.second.first + p2.second.second);
    }
};

Compare *Compare::c;

string befs(vector<vector<int>> matrix, pair<int,int> start, pair<int,int> goal) {
    priority_queue <pair<int,int>, vector<pair<int,int>>, Compare > pq;
    unordered_map<pair<int,int>, pair<string, pair<int,int>>, hash_pair> priors;
    Compare::instance()->setMatrix(matrix);
    pq.push(start);
    vector<vector<bool>> visited = makeVisited(matrix);
    visited[start.first][start.second] = true;
    while (!pq.empty()) {
        int i = pq.top().first;
        int j = pq.top().second;
        pq.pop();
        if ((i == goal.first) && (j == goal.second)) {
            pq = priority_queue <pair<int,int>, vector<pair<int,int>>, Compare >();
        } else {
            if ((i + 1 < matrix.size()) && (visited[i + 1][j] == false) && (matrix[i+1][j]>=0)) {
                priors[{i+1,j}] = {"Down",{i,j}};
                pq.push({i + 1, j});
                visited[i + 1][j] = true;
            }
            if ((j + 1 < matrix[i].size()) && (visited[i][j + 1] == false) && (matrix[i][j+1]>=0)) {
                priors[{i,j+1}] = {"Right",{i,j}};
                pq.push({i, j + 1});
                visited[i][j + 1] = true;
            }
            if ((i > 0) && (visited[i - 1][j] == false) && (matrix[i-1][j]>=0)) {
                priors[{i-1,j}] = {"Up",{i,j}};
                pq.push({i - 1, j});
                visited[i - 1][j] = true;
            }
            if ((j > 0) && (visited[i][j - 1] == false) && (matrix[i][j-1]>=0)) {
                priors[{i,j-1}] = {"Left",{i,j}};
                pq.push({i, j - 1});
                visited[i][j - 1] = true;
            }
        }
    }
    return recString(start, goal, matrix, priors).first;
}

/*
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                      A*
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/

double getH(int row, int col, pair<int,int> dest)
{
    // Return using the distance formula
    return ((double)sqrt ((row-dest.first)*(row-dest.first)
                          + (col-dest.second)*(col-dest.second)));
}

bool isValid (pair<int,int> place, vector<vector<int>> matrix, vector<vector<bool>> visited) {
    return ((place.first >= 0) && (place.second >= 0) && (place.first < matrix.size())
            && (place.second < matrix[0].size()) && (matrix[place.first][place.second] >=0) && (!visited[place.first][place.second]));
}

bool comparePair(pair<double,double> p1, pair<double ,double>p2) {
    return ((p1.first == p2.first) && (p1.second == p2.second));
}

bool compareF(pair<int,double> p1, pair<int ,double>p2) {
    return (p1.first + p1.second) > (p2.first + p2.second);
}

string astar(vector<vector<int>> matrix, pair<int,int> start, pair<int,int> goal) {
    priority_queue <pair<pair<int,int>, pair<int,double>>, vector<pair<pair<int,int>, pair<int,double>>>, Compare > openList;
    priority_queue <pair<pair<int,int>, pair<int,double>>, vector<pair<pair<int,int>, pair<int,double>>>, Compare > closeList;
    unordered_map<pair<int,int>, pair<string, pair<int,int>>, hash_pair> priors;
    vector<vector<bool>> visited = makeVisited(matrix);

    openList.push({{start.first,start.second}, {0,0}});
    visited[start.first][start.second] = true;
    while (!openList.empty()) {
        pair<pair<int,int>,pair<int,double>> q = openList.top();
        openList.pop();
        int i = q.first.first;
        int j = q.first.second;
        int g = q.second.first;

        /*
         * make neighbors list
         */
        vector<pair<pair<int,int>,pair<int,double>>> neighbors;
        if (isValid({i-1,j}, matrix, visited)) {
            neighbors.push_back({{i - 1, j}, {g + matrix[i - 1][j], getH(i - 1, j, goal)}});
            priors[neighbors[neighbors.size()-1].first] = {"Left",{i,j}};
            visited[i-1][j] = true;
        } if (isValid({i+1,j}, matrix, visited)) {
            neighbors.push_back({{ i + 1, j}, { g + matrix[i + 1][j], getH(i + 1, j, goal)}});
            priors[neighbors[neighbors.size()-1].first] =  {"Right",{i,j}};
            visited[i+1][j] = true;
        } if (isValid({i,j-1}, matrix, visited)) {
            neighbors.push_back( {{ i, j - 1}, { g + matrix[i][j - 1], getH(i, j - 1, goal)}});
            priors[neighbors[neighbors.size()-1].first] = {"Up",{i,j}};
            visited[i][j-1] = true;
        }if (isValid({i,j+1}, matrix, visited)) {
            neighbors.push_back({{ i, j + 1}, { g + matrix[i][j + 1], getH(i, j + 1, goal)}});
            priors[neighbors[neighbors.size()-1].first] =  {"down", {i,j}};
            visited[i][j+1] = true;
        }


        for (int i = 0; i < neighbors.size(); i++) {
            // if current neighbors[i] is the goal
            if (comparePair(neighbors[i].first, goal)) {
                return recString(start, goal, matrix, priors).first;
            }
            if (!(((!openList.empty()) && (comparePair(neighbors[i].first, openList.top().first)) && (compareF(neighbors[i].second, openList.top().second)))
                  || (!closeList.empty()) && (comparePair(neighbors[i].first, closeList.top().first)) && (compareF(neighbors[i].second, openList.top().second)))) {
                openList.push(neighbors[i]);
            }
        }
        closeList.push(q);
    }
}


#endif //SEARCH__SEARCHALGOS_H_