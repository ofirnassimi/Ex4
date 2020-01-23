//
// Created by ofir on 20/01/2020.
//

//#ifndef EX4_MATRIX_H
#define EX4_MATRIX_H

#include <iostream>
#include <vector>
#include "Searchable.h"
#include "State.h"

using namespace std;

class Matrix : public Searchable<pair<int, int>> {
    vector<vector<int>> mat;
    State<pair<int, int>> initialState;
    State<pair<int, int>> goalState;

public:
    Matrix(vector<vector<int>> &m, State<pair<int, int>> &init, State<pair<int, int>> goal) : mat(m), initialState(init), goalState(goal) {

    }

    State<pair<int, int>>* getInitialState() {
        return &this->initialState;
    }

    bool isGoalState(State<pair<int, int>> s) {
        if (goalState.getState().first == s.getState().first) {
            if (goalState.getState().second == s.getState().second) {
                return true;
            }
        }
        return false;
    }

    list<State<pair<int, int>>*> getAllPossibleStates(State<pair<int, int>> &s) {
        int x = s.getState().first;
        int y = s.getState().second;
        list<State<pair<int, int>>*> succerssors;

        //TODO: change costs!!!!
        //TODO: Change the way of checking if this variable is in matrix borders!!!
        int leftCost = mat[x][y - 1];
        int rightCost = mat[x][y + 1];
        int upCost = mat[x - 1][y];
        int downCost = mat[x + 1][y];

        if (leftCost != NULL) {
            pair<int, int> l;
            l.first = x;
            l.second = y;
            //State<pair<int, int>>* sp = new State<pair<int, int>>(l, left, &s);
            succerssors.push_back(new State<pair<int, int>>(l, leftCost, &s));
        }
        if (rightCost != NULL) {
            pair<int, int> r;
            r.first = y + 1;
            r.second = x;
            //State<pair<int, int>>* sp = new State<pair<int, int>>(r, right, &s);
            succerssors.push_back(new State<pair<int, int>>(r, rightCost, &s));
        }
        if (upCost != NULL) {
            pair <int, int> u;
            u.first = y;
            u.second = x - 1;
            succerssors.push_back(new State<pair<int, int>>(u, upCost, &s));
        }
        if (downCost != NULL) {
            pair <int, int> d;
            d.first = y;
            d.second = x + 1;
            succerssors.push_back(new State<pair<int, int>>(d, downCost, &s));
        }

        return succerssors;
    }
};