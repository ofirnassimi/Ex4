//
// Created by ofir on 26/01/2020.
//

#ifndef EX4_BFS_H
#define EX4_BFS_H

#include "State.h"
#include <set>
#include "Searchable.h"
#include <list>
#include <queue>
#include <iostream>
#include "Searchable.h"
#include "Searcher.h"

//problem: Matrix, solution: string
template <typename P, typename S>
class BFS : public Searcher<P,S> {
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
    BFS(vector<vector<int>> m, pair<int,int> s, pair<int,int> g) {
        this->matrix = m;
        this->start = s;
        this->goal = g;
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


    S search(P &p) {
        queue<pair<int, int>> next;
        vector<vector<bool>> visited = makeVisited(matrix);
        unordered_map<pair<int, int>, pair<string, pair<int, int>>, hash_pair> priors;
        next.push(start);
        visited[start.first][start.second] = true;

        while (!next.empty()) {
            int i = next.front().first;
            int j = next.front().second;
            if (!((goal.first == i) && goal.second == j)) {
                next.pop();

                if ((i + 1 < matrix.size()) && (visited[i + 1][j] == false) && (matrix[i + 1][j] >= 0)) {
                    priors[{i + 1, j}] = {"Down", {i, j}};
                    next.push({i + 1, j});
                    visited[i + 1][j] = true;
                }
                if ((j + 1 < matrix[i].size()) && (visited[i][j + 1] == false) && (matrix[i][j + 1] >= 0)) {
                    priors[{i, j + 1}] = {"Right", {i, j}};
                    next.push({i, j + 1});
                    visited[i][j + 1] = true;
                }
                if ((i > 0) && (visited[i - 1][j] == false) && (matrix[i - 1][j] >= 0)) {
                    priors[{i - 1, j}] = {"Up", {i, j}};
                    next.push({i - 1, j});
                    visited[i - 1][j] = true;
                }
                if ((j > 0) && (visited[i][j - 1] == false) && (matrix[i][j - 1] >= 0)) {
                    priors[{i, j - 1}] = {"Left", {i, j}};
                    next.push({i, j - 1});
                    visited[i][j - 1] = true;
                }
            } else {
                next = queue<pair<int, int>>();
            }
        }
        return (recString(start, goal, matrix, priors).first);
    }


    int getNumberOfNodesEvaluated() {
        return counterSteps;
    }


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


    //creates a string of the path
    pair<string, int> recString(pair<int,int> start, pair<int,int> end, vector<vector<int>> matrix,
                                unordered_map<pair<int,int>, pair<string, pair<int,int>>, hash_pair> priors) {
        stringstream s;

        if ((end.first == start.first) && (end.second == start.second)) {
            return {"",matrix[end.first][end.second]};
        } else {
            pair<string,int> p = recString(start, priors.at(end).second, matrix, priors);
            s << p.first << priors.at(end).first << " (" << p.second + matrix[end.first][end.second] << ") ";
            return {s.str(),p.second+matrix[end.first][end.second]};
        }
    }
};

#endif //EX4_BFS_H