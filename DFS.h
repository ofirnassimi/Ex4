//
// Created by ofir on 29/01/2020.
//

#ifndef EX4_DFS_H
#define EX4_DFS_H

#include "State.h"
#include <set>
#include "Searchable.h"
#include <list>
#include <queue>
#include <iostream>
#include <sstream>
#include "Searchable.h"
#include "Searcher.h"

//problem: Matrix, solution: string
template <typename P, typename S>
class DFS : public Searcher<P,S> {
private:
    int evaluatedNodes;
    int counterSteps = 0;
    list<State<pair<int, int>>> visited;
    list<State<pair<int, int>>> queueC;
    list<State<pair<int, int>>> way;
    vector<vector<int>> matrix;
    pair<int,int> start;
    pair<int,int> goal;

public:
    DFS(vector<vector<int>> m, pair<int,int> s, pair<int,int> g) {
        this->matrix = m;
        this->start = s;
        this->goal = g;
    }

    S search(P &p) {
        vector<vector<int>> visited = makeVisited(matrix);
        return (recDFS(matrix, visited, start, goal,new bool(false), matrix[start.first][start.second]).str());
    }


    int getNumberOfNodesEvaluated() {
        return counterSteps;
    }


    // makes a 'visited' bool matrix to match the tested matrix and initial all of the values to be false.
    vector<vector<int>> makeVisited(vector<vector<int>> matrix) {
        vector<vector<int>> ret;
        vector<int> row;
        for(int i = 0; i < matrix.size(); i++) {
            for(int j = 0; j < matrix[i].size(); j++) {
                row.push_back(false);
            }
            ret.push_back(row);
            row.clear();
        }
        return ret;
    }


    stringstream recDFS(vector<vector<int>> matrix, vector<vector<int>> &visited, pair<int,int> start, pair<int,int> goal, bool *end, int count){
        int i = start.first, j = start.second;

        stringstream s;
        visited[i][j] = true;

        if (!((goal.first == i) && (goal.second == j))) {
            //checks neighbors
            if (((i + 1 < matrix.size()) && (visited[i + 1][j] == false)) && !*end) {
                count += matrix[i+1][j];
                s << "Down (" << count << ") " << recDFS(matrix, visited,{i+1, j} , goal, end, count).str();
                return s;
            }
            if (((j + 1 < matrix[i].size()) && (visited[i][j + 1] == false)) && !*end) {
                count += matrix[i][j+1];
                s << "Right (" << count << ") " << recDFS(matrix, visited, {i, j+1}, goal, end,count).str();
                return s;
            }
            if (((i > 0) && (visited[i - 1][j] == false)) && !*end) {
                count += matrix[i-1][j];
                s << "Up (" << count << ") " << recDFS(matrix, visited, {i-1, j}, goal,end,count).str();
                return s;
            }
            if (((j > 0) && (visited[i][j - 1] == false)) && !*end) {
                count += matrix[i][j-1];
                s << "Left (" << count << ") " << recDFS(matrix, visited,{i, j-1}, goal,end,count).str();
                return s;
            }
        } else {
            *end = true;
            return s;
        }
    }
};

#endif //EX4_DFS_H
