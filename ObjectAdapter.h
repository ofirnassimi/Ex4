//
// Created by ofir on 23/01/2020.
//

#ifndef EX4_OBJECTADAPTER_H
#define EX4_OBJECTADAPTER_H

#include "Solver.h"
#include "Matrix.h"
#include "Searcher.h"
#include "BFS.h"

using namespace std;

class ObjectAdapter : public Solver<Matrix, string> {
//class ObjectAdapter : public Solver<list<string>, string> {
//    Searcher<Matrix, list<State<pair<int, int>>>>* s;

public:
    string solve(Matrix m) {
        Searcher<Matrix, string>* bfs = new BFS<Matrix, string>();
        //Searcher<string, pair<int, int>>* bfs = new BFS<string, pair<int, int>>();

        string solution = bfs->search(m);
        return solution;
    }

    //ObjectAdapter(Searcher<Matrix, list<State<pair<int, int>>>>* searchS) : s(searchS) {}

    //we get a list of values and 2 last vars contains initial and goal
//    string solve(list<string> problem) {
////        string goalState = problem.back();
////        problem.pop_back();
////        string initialState = problem.back();
////        problem.pop_back();
////
////        Matrix m = buffsToMatrix(problem, initialState, goalState);
//
//        Searcher<string, pair<int, int>>* bfs = new BFS<string, pair<int, int>>();
//        bfs->search(m);
//    }

//    Matrix buffsToMatrix(list<string> buffers, string init, string goal) {
//        vector<vector<int>> vecs = createVector(buffers.front());
//        buffers.pop_front();
//        while (!buffers.empty()) {
//            vecs = addToMat(buffers.front(), vecs);
//            buffers.pop_front();
//        }
//
//        pair<int, int> is = stringToPair(init);
//        pair<int, int> gs = stringToPair(goal);
//        int initialCost = vecs[is.first][is.second];
//        int goalCost = vecs[gs.first][gs.second];
//
//        State<pair<int, int>> initialState = State<pair<int, int>>(is, initialCost, NULL);
//        State<pair<int, int>> goalState = State<pair<int, int>>(gs, goalCost, NULL);
//
//        return Matrix(vecs, initialState, goalState);
//    }
//
//
//    static vector<vector<int>> addToMat(string buffer, vector<vector<int>> mat) {
//        vector<int> temp;
//        string curr = "";
//        int vecCount = 0;
//        int len = buffer.length();
//
//        for (int i = 0; i < len; i++) {
//            if ((buffer[i] == ' ') || (buffer[i] == ',')) {
//                if (curr != "") {
//                    temp.push_back(stoi(curr));
//                    curr = "";
//                    vecCount++;
//                }
//            } else {
//                curr += buffer[i];
//            }
//        }
//        temp.push_back(stoi(curr));
//        mat.push_back(temp);
//        return mat;
//    }
//
//    //If it's the first time we read to a buffer, we create a vector and return it
//    static vector<vector<int>> createVector(string buffer) {
//        vector<vector<int>> mat;
//        vector<int> temp;
//        string curr = "";
//        int vecCount = 0;
//        int len = buffer.length();
//
//        for (int i = 0; i < len; i++) {
//            if ((buffer[i] == ' ') || (buffer[i] == ',')) {
//                if (curr != "") {
//                    temp.push_back(stoi(curr));
//                    //mat[0][vecCount] = stoi(curr);
//                    curr = "";
//                    vecCount++;
//                }
//            } else {
//                curr += buffer[i];
//            }
//        }
//        //add the last "curr" to the temp vector
//        temp.push_back(stoi(curr));
//
//        //push temp to mat
//        mat.push_back(temp);
//
//        return mat;
//    }
//
//    pair<int, int> stringToPair(string str) {
//        vector<int> temp;
//        int x, y;
//        string curr = "";
//        int len = str.length();
//        int i = 0;
//
//        for (int i = 0; i < len; i++) {
//            if ((str[i] == ' ') || (str[i] == ',')) {
//                if (curr != "") {
//                    temp.push_back(stoi(curr));
//                    curr = "";
//                }
//            } else {
//                curr += str[i];
//            }
//        }
//        temp.push_back(stoi(curr));
//
//        pair<int, int> ret;
//        ret.first = temp.at(0);
//        ret.second = temp.at(1);
//
//        return ret;
//    }
};

#endif //EX4_OBJECTADAPTER_H
